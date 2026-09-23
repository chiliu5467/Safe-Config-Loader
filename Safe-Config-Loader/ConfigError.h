#pragma once

#include <stdexcept>

class ConfigError : public std::runtime_error
{
public:
    using std::runtime_error::runtime_error;
};

class ConfigFormatError : public ConfigError
{
public:
    using ConfigError::ConfigError;
};

class ConfigValueError : public ConfigError
{
public:
    using ConfigError::ConfigError;
};
