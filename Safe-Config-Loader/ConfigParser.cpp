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
            try
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
            catch (const std::invalid_argument& e)
            {
                std::cerr << "無效的數值格式: [" << key << "] = " << value << "\n";
            }
            catch (const std::out_of_range& e)
            {
                std::cerr << "數值超出範圍: [" << key << "] = " << value << "\n";
            }
        }
    }

    return config;
}