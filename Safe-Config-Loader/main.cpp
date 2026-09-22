#include <iostream>

#include "ConfigParser.h"

void TestException(std::vector<std::string> lines)
{
    try
    {
        Config config = ParseConfig(lines);

        std::cout << "Width: " << config.width << "\n";
        std::cout << "Height: " << config.height << "\n";
        std::cout << "Fullscreen: " << (config.fullscreen ? "true" : "false") << "\n";
    }
    catch (const std::exception& e)
    {
        std::cout << "Config error: "
            << e.what() << '\n';
    }
}

int main()
{
    std::vector<std::string> invalidCase{
    "width=abc",
    "height=1080",
    "fullscreen=true"
        };
    std::vector<std::string> validCase{
    "width=1920",
    "height=1080",
    "fullscreen=true"
    };

    TestException(invalidCase);
    TestException(validCase);
    return 0;
}