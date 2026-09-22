#include "ConfigParser.h"

#include <sstream>
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
            throw std::runtime_error("Invalid config format");
        }

        std::string key = line.substr(0, separator);
        std::string value = line.substr(separator + 1);

        std::cout << "Key: [" << key << "], Value: [" << value << "]\n";

        if (key == "width")
        {
            config.width = std::stoi(value);
        }
        else if (key == "height")
        {
            config.height = std::stoi(value);
        }
        else if (key == "fullscreen")
        {
            if (value == "true")
            {
                config.fullscreen = (value == "true" || value == "1");
            }
            else if (value == "false")
            {
                config.fullscreen = (value == "false" || value == "0");
            }
            else
            {
                throw std::runtime_error("Invalid boolean value: " + value);
            }
        }
        else
        {
            throw std::runtime_error("Unknown config key: " + key);
        }
    }

    return config;
}