#include "types.h"
#include <iostream>

template <typename... Args> void logd(Args... args) { ((std::cout << args << " "), ...) << std::endl; };

void print_usage() {
  std::cout << "Usage: frename -d <directory> -s <pattern> -l <delimiter> [-r]\n\n"
               "  -d <directory>   Directory containing files to rename\n"
               "  -s <pattern>     Naming pattern to match against\n"
               "  -l <delimiter>   Delimiter used after pattern\n"
               "  -r               Dry run: preview renames without applying them\n"
               "  -h               Show this help message\n";
}

void print_files(const std::vector<rename_pair> &data) {
  for (const rename_pair &item : data) {
    std::cout << item.old_path << " : " << item.new_path << std::endl;
  }
}
