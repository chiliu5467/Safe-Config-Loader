#include "ConfigParser.h"
#include "ConfigError.h"

#include <string>
#include <stdexcept>
#include <iostream>

Config ParseConfig(const std::vector<std::string>& lines)
{
    Config config{};

    for (const auto& line : lines)
    {
        auto separator = line.find('=');
        if (separator == std::string::npos)
        {
            throw ConfigFormatError("Invalid config format");
        }

        std::string key = line.substr(0, separator);
        std::string value = line.substr(separator + 1);

        std::cout << "Key: [" << key << "], Value: [" << value << "]\n";

        if (key == "width")
        {
            try {
                config.width = std::stoi(value);
            }
            catch (const std::invalid_argument& e) {
                throw ConfigValueError("Invalid numeric value for: " + key);
            }
        }
        else if (key == "height")
        {
            try {
                config.height = std::stoi(value);
            }
            catch (const std::exception&) {
				throw ConfigValueError("Invalid numeric value for: " + key);
            }
        }
        else if (key == "fullscreen")
        {
            if (value == "true")
            {
                config.fullscreen = true;
            }
            else if (value == "false")
            {
                config.fullscreen = false;
            }
            else
            {
                throw ConfigValueError("Invalid boolean value: " + value);
            }
        }
        else
        {
            throw ConfigValueError("Unknown config key: " + key);
        }
    }

    return config;
}