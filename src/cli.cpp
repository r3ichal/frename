#include "types.h"
#include <iostream>
#include <string>
#include <utility>

void parse_args(int arg_count, char *arg_values[], options_table opt) {
  for (size_t i = 1; std::cmp_less(i, arg_count); i++) {
    std::string arg = arg_values[i];

    if (arg == "--help") {
      *opt.find('h')->second.triggered = true;
      break;
    }

    const char *arg_ptr = arg.c_str();
    if (*arg_ptr == '-') {
      arg_ptr++;
      auto it = opt.find(*arg_ptr);

      if (it == opt.end()) {
        std::cout << "no valid argument" << std::endl;
      } else if (it->second.takes_value) {
        if (std::cmp_greater_equal(i + 1, arg_count)) {
          std::cout << "missing value";
          continue;
        }
        i++;
        *(it->second.target) = arg_values[i];
      } else if (it->second.triggered) {
        *it->second.triggered = true;
      }
    }
  }
}