#include <stdexcept>
#include <string>

bool is_valid_int(const std::string &str, int &value) {
  try {
    size_t pos = 0;
    value = std::stoi(str, &pos);

    return pos == str.length();
  } catch (const std::invalid_argument &) {
    return false;
  } catch (const std::out_of_range &) {
    return false;
  }
}