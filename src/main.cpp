#include "cli.h"
#include "fs_utils.h"
#include "log.h"
#include "string_utils.h"
#include "types.h"
#include <filesystem>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

int main(int arg_count, char *arg_values[]) {
  app_config config;

  options_table options = {
    {'d', {true, &config.directory, nullptr}},
    {'s', {true, &config.std_input, nullptr}},
    {'l', {true, &config.delimiter, nullptr}},
    {'r', {false, nullptr, &config.should_preview}},
    {'h', {false, nullptr, &config.show_help}},
  };

  parse_args(arg_count, arg_values, options);

  if (config.show_help) {
    print_usage();
    return 0;
  }

  fs::path dir_path = config.directory;

  if (fs::exists(dir_path) && fs::is_directory(dir_path)) {
    std::string standard = validate_standard(config.std_input, config.delimiter);
    gap_info info = get_gaps(dir_path, standard);
    std::vector<rename_pair> data = path_data(dir_path, standard, info, config.delimiter);
    rename_data(config.should_preview, data);
  } else {
    std::cerr << "Directory not found." << std::endl;
    return 1;
  }

  return 0;
}