#include "int_utils.h"
#include "string_utils.h"
#include "types.h"
#include <cstddef>
#include <iostream>
#include <utility>
#include <vector>

// get_gaps - from directory and std string get an ordered set of gaps, and highest index between them
gap_info get_gaps(const fs::path &directory, const std::string &standard) {
  fs::directory_iterator it(directory);
  fs::directory_iterator end;
  std::set<int> taken;
  gap_info info;

  int value = 0;

  for (; it != end; it++) {
    if (fs::is_regular_file(*it)) {
      std::string stem = it->path().stem().string();
      if (stem.starts_with(standard)) {
        std::string cut = stem.substr(standard.length());
        if (is_valid_int(cut, value)) {
          taken.insert(value);
          if (std::cmp_less(info.highest, value)) {
            info.highest = value;
          }
        }
        continue;
      }
    }
  }

  if (!taken.empty()) {
    for (size_t i = 0; std::cmp_less(i, *taken.rbegin()); i++) {
      if (!taken.contains(i)) {
        info.gaps.insert(i);
      }
    }
  }

  return info;
}

std::vector<rename_pair>
path_data(const fs::path &directory, const std::string &standard, gap_info &info, const std::string &delimiter) {
  std::vector<rename_pair> data;
  fs::directory_iterator it(directory);
  fs::directory_iterator end;

  size_t i = info.highest == 0 ? info.highest : info.highest + 1;
  int valid_value = 0;

  for (; it != end; it++) {
    if (fs::is_regular_file(*it)) {
      std::string stem = it->path().stem().string();
      size_t index_position = split(stem, delimiter)[0].size() + delimiter.size();
      if (!stem.starts_with(standard) || !is_valid_int(stem.substr(index_position), valid_value)) {
        fs::path path;
        if (!info.gaps.empty()) {
          int id = *info.gaps.begin();
          path = it->path().parent_path() / (standard + std::to_string(id) + it->path().extension().string());
          info.gaps.erase(info.gaps.begin());
        } else {
          path = it->path().parent_path() / (standard + std::to_string(i) + it->path().extension().string());
          i++;
        }
        data.push_back({it->path(), path});
      }
    }
  }

  return data;
}

void rename_data(const bool &should_preview, const std::vector<rename_pair> &data) {

  if (should_preview) {
    std::cout << "You are about to rename " << data.size()
              << " files. Remove -r and run the command again to apply changes" << std::endl;

    for (const rename_pair &item : data) {
      std::cout << item.old_path << " : " << item.new_path << std::endl;
    }
  } else {
    for (const rename_pair &item : data) {
      std::cout << item.old_path << " : " << item.new_path << std::endl;
    }

    int success_count = 0;
    for (size_t i = 0; i < data.size(); i++) {
      std::error_code ec;
      fs::rename(data[i].old_path, data[i].new_path, ec);
      if (!ec) {
        success_count++;
      } else {
        std::cerr << "Failed to rename " << data[i].old_path.filename() << " : " << ec.message() << '\n';
      }
    }
    std::cout << "Successfully renamed " << success_count << " files.\n";
  }
}