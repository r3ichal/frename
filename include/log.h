#pragma once
#include "types.h"
#include <iostream>

template <typename... Args> void logd(Args... args) { ((std::cout << args << " "), ...) << std::endl; };

void print_usage();

void print_files(const std::vector<rename_pair> &data);