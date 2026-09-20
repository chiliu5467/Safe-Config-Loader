#pragma once

#include "Config.h"

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>

Config ParseConfig(const std::vector<std::string>& lines);