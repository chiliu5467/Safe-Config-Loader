#pragma once

#include "Config.h"

#include <string>
#include <vector>

Config ParseConfig(const std::vector<std::string>& lines);

bool TryLoadConfig(
    const std::vector<std::string>& lines,
    Config& output);