#include <iostream>

#include "ConfigParser.h"
#include "ConfigError.h"

void TestException(const std::vector<std::string>& lines)
{
    try
    {
        Config config = ParseConfig(lines);
    }
    catch (const ConfigValueError& e)
    {
        std::cout << "Config Value error: "
            << e.what() << '\n';
    }
    catch (const ConfigFormatError& e)
    {
        std::cout << "Config Format error: "
            << e.what() << '\n';
    }
    catch (const std::exception& e)
    {
        std::cout << "Some other std::exception error: "
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

    std::vector<std::string> unknownKeyCase{
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
    TestException(unknownKeyCase);
    TestException(validFalseCase);
    TestException(invalidBooleanCase);

    return 0;
}