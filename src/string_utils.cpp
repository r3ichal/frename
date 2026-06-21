#include "string_utils.h"
#include <algorithm>
#include <cctype>
#include <string>
#include <vector>

std::vector<std::string> split(const std::string &string, const std::string &del) {

  if (del.empty()) {
    return {string};
  }

  std::vector<std::string> result;
  size_t start = 0, pos;

  result.reserve(string.size() / del.size() + 1);

  while ((pos = string.find(del, start)) != std::string::npos) {
    result.push_back(string.substr(start, pos - start));
    start = pos + del.length();
  }

  result.push_back(string.substr(start));
  return result;
}

std::string join(const std::vector<std::string> &words, const std::string &delimiter) {
  if (words.empty())
    return "";

  size_t total_size = delimiter.length() * (words.size() - 1);
  for (const auto &str : words) {
    total_size += str.length();
  }

  std::string result;
  result.reserve(total_size);

  result += words[0];
  for (size_t i = 1; i < words.size(); ++i) {
    result += delimiter;
    result += words[i];
  }

  return result;
}

std::string trim(const std::string &str) {
  auto callback = [](unsigned char c) { return std::isspace(c); };

  std::string::const_iterator start = std::find_if_not(str.begin(), str.end(), callback);
  std::string::const_iterator end = std::find_if_not(str.rbegin(), str.rend(), callback).base();

  if (end == str.begin()) {
    end = str.end();
  }

  return std::string(start, end);
}

std::string validate_standard(const std::string &standard, const std::string &delimiter) {
  std::string validated_string = trim(standard);
  if (!validated_string.ends_with(delimiter)) {
    validated_string += delimiter;
  }

  return validated_string;
}
