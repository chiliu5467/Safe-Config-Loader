#include "ConfigParser.h"

Config ParseConfig(const std::vector<std::string>& lines)
{
    Config config;

    for (const auto& line : lines)
    {
        std::stringstream ss(line);
        std::string key, value;

        if (std::getline(ss, key, '=') && std::getline(ss, value))
        {
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
                config.fullscreen = (value == "true" || value == "1");
            }
        }
    }

    return config;
}