#pragma once
#include "types.h"

gap_info get_gaps(const fs::path &directory, const std::string &standard);

std::vector<rename_pair>
path_data(const fs::path &directory, const std::string &standard, gap_info &info, const std::string &delimiter);

void rename_data(const bool &should_preview, const std::vector<rename_pair> &data);