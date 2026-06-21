#pragma once
#include <filesystem>
#include <set>
#include <unordered_map>
#include <vector>

namespace fs = std::filesystem;
using path_vector = std::vector<std::vector<fs::path>>;

struct rename_pair {
  fs::path old_path;
  fs::path new_path;
};

struct gap_info {
  std::set<int> gaps;
  size_t highest = 0;
};

struct option_spec {
  bool takes_value;
  std::string *target;
  bool *triggered;

  option_spec(bool tv, std::string *tg, bool *tr) : takes_value(tv), target(tg), triggered(tr) {}
};

using options_table = std::unordered_map<char, option_spec>;

struct app_config {
  std::string directory;
  std::string std_input;
  std::string delimiter = "_";
  bool should_preview = false;
  bool show_help = false;
};
