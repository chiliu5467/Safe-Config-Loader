#include <iostream>

#include "ConfigParser.h"

void TestException()
{
    try
    {
        std::vector<std::string> lines{
        "width=1920",
        "height=1080",
        "fullscreen=true"
        };

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
    TestException();
    return 0;
}