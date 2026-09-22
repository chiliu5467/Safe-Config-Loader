#include <iostream>

#include "ConfigParser.h"

void TestException(std::vector<std::string> lines)
{
    try
    {
        Config config = ParseConfig(lines);
    }
    catch (const std::exception& e)
    {
        std::cout << "Config error: "
            << e.what() << '\n';
    }
}

int main()
{
    std::vector<std::string> validCase{
    "width=1920",
    "height=1080",
    "fullscreen=true"
    };

    std::vector<std::string> invalidIntegerCase{
    "width=abc",
    "height=1080",
    "fullscreen=true"
    };

    std::vector<std::string> missingCase{
    "width1920",
    "height=1080",
    "fullscreen=true"
    };

    std::vector<std::string> unkownKeyCase{
    "volume=80",
    "height=1080",
    "fullscreen=true"
    };

    std::vector<std::string> validFalseCase{
    "width=1920",
    "height=1080",
    "fullscreen=false"
    };

    std::vector<std::string> invalidBooleanCase{
    "width=1920",
    "height=1080",
    "fullscreen=yes"
    };

    TestException(validCase);
    TestException(invalidIntegerCase);
    TestException(missingCase);
    TestException(unkownKeyCase);
    TestException(validFalseCase);
    TestException(invalidBooleanCase);

    return 0;
}