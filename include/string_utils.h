#pragma once
#include <string>
#include <vector>

std::vector<std::string> split(const std::string &string, const std::string &del);

std::string join(const std::vector<std::string> &words, const std::string &delimiter);

std::string trim(const std::string &str);

std::string validate_standard(const std::string &standard, const std::string &delimiter = "_");