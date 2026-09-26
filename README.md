# Safe Config Loader

A small C++ project for practicing robust configuration parsing, exception handling, custom exception types, and exception-safe API design.

The project parses simple `key=value` configuration data and converts it into a strongly typed `Config` object while validating malformed or unsupported input.

## Features

- Parses configuration data from `std::vector<std::string>`
- Supports:
  - `width`
  - `height`
  - `fullscreen`
- Validates malformed configuration lines
- Detects unknown configuration keys
- Validates numeric values
- Validates boolean values
- Uses custom exception types
- Translates low-level standard exceptions into domain-specific exceptions
- Provides both:
  - an exception-based parsing API
  - a `noexcept` wrapper API
- Preserves the original configuration when loading fails

## Supported Configuration Format

Example input:

~~~text
width=1920
height=1080
fullscreen=true
~~~

Supported keys:

| Key | Type | Example |
| --- | --- | --- |
| `width` | `int` | `1920` |
| `height` | `int` | `1080` |
| `fullscreen` | `bool` | `true` / `false` |

Invalid values such as:

~~~text
width=abc
fullscreen=yes
volume=80
width1920
~~~

are rejected with meaningful errors.

## Project Structure

~~~text
Safe-Config-Loader/
├── Config.h
├── ConfigError.h
├── ConfigParser.h
├── ConfigParser.cpp
└── main.cpp
~~~

### `Config.h`

Defines the parsed configuration data:

~~~cpp
struct Config
{
    int width;
    int height;
    bool fullscreen;
};
~~~

### `ConfigParser`

The main parsing function is:

~~~cpp
Config ParseConfig(
    const std::vector<std::string>& lines);
~~~

It parses and validates all input.

If parsing fails, it throws a domain-specific exception.

## Custom Exception Hierarchy

The project defines a small exception hierarchy:

~~~text
std::runtime_error
        │
        └── ConfigError
             │
             ├── ConfigFormatError
             │
             └── ConfigValueError
~~~

### `ConfigFormatError`

Used when the structure of a configuration line is invalid.

Example:

~~~text
width1920
~~~

### `ConfigValueError`

Used when the configuration format is valid, but the value or key is invalid.

Examples:

~~~text
width=abc
fullscreen=yes
volume=80
~~~

This allows callers to distinguish configuration-specific failures using exception types instead of relying only on error-message strings.

## Exception Translation

Standard-library operations such as:

~~~cpp
std::stoi(value);
~~~

can throw exceptions such as:

~~~cpp
std::invalid_argument
std::out_of_range
~~~

The parser catches these lower-level exceptions and translates them into domain-specific errors:

~~~text
std::invalid_argument
        ↓
ConfigValueError
~~~

For example:

~~~cpp
catch (const std::invalid_argument&)
{
    throw ConfigValueError(
        "Invalid numeric value for: " + key);
}
~~~

This keeps implementation details such as `std::stoi` hidden from higher-level callers.

## Exception-Safe Loading API

The project also provides:

~~~cpp
bool TryLoadConfig(
    const std::vector<std::string>& lines,
    Config& output) noexcept;
~~~

This API converts exception-based parsing into a boolean success/failure interface.

### Success

~~~text
ParseConfig succeeds
        ↓
temporary Config is created
        ↓
output is updated
        ↓
return true
~~~

### Failure

~~~text
ParseConfig throws
        ↓
exception is caught
        ↓
temporary Config is discarded
        ↓
original output remains unchanged
        ↓
return false
~~~

Example:

~~~cpp
Config config{ 800, 600, false };

bool success = TryLoadConfig(lines, config);
~~~

If parsing fails, `config` still contains:

~~~text
width: 800
height: 600
fullscreen: false
~~~

This avoids leaving the caller with a partially modified configuration.

## Example Usage

~~~cpp
std::vector<std::string> lines{
    "width=1920",
    "height=1080",
    "fullscreen=true"
};

try
{
    Config config = ParseConfig(lines);

    std::cout << config.width << '\n';
    std::cout << config.height << '\n';
    std::cout << std::boolalpha
              << config.fullscreen << '\n';
}
catch (const ConfigValueError& e)
{
    std::cout << "Config value error: "
              << e.what() << '\n';
}
catch (const ConfigFormatError& e)
{
    std::cout << "Config format error: "
              << e.what() << '\n';
}
catch (const std::exception& e)
{
    std::cout << "Unexpected error: "
              << e.what() << '\n';
}
~~~

## Test Cases

The project includes tests for:

- valid configuration
- `fullscreen=true`
- `fullscreen=false`
- invalid `width`
- invalid `height`
- missing `=`
- unknown configuration key
- invalid boolean value
- successful `TryLoadConfig`
- failed `TryLoadConfig`
- preservation of the original configuration after failure

Example invalid inputs:

~~~text
width=abc
height=hello
fullscreen=yes
volume=80
width1920
~~~

## What I Learned

This project was built to practice several important C++ error-handling concepts.

### Exception propagation

An exception does not always need to be handled where it is thrown.

A lower-level function can detect a problem and allow the exception to propagate to a caller that has enough context to decide what should happen.

### Stack unwinding

When an exception propagates through the call stack, local objects in exited scopes are destroyed automatically.

This connects exception handling directly with RAII and deterministic destruction.

### Error ownership

The place where an error is detected is not always the best place to handle it.

A useful question is:

> Does this layer have enough context to meaningfully recover from the error?

If not, the error can propagate to a higher-level caller.

### Custom exceptions

Custom exception types provide semantic information through the type system.

Instead of treating every error as a generic `std::runtime_error`, callers can distinguish between format errors and value errors.

### Exception translation

Low-level implementation errors can be translated into higher-level domain errors.

For example:

~~~text
std::invalid_argument
        ↓
ConfigValueError
~~~

This prevents callers from depending on implementation details.

### `noexcept`

`noexcept` is an API contract stating that exceptions must not escape the function.

`TryLoadConfig()` uses this contract because it catches parsing errors internally and converts them into a boolean result.

### Exception safety

The loader parses data into a temporary `Config` first.

Only after parsing succeeds is the caller's output object updated.

This helps preserve the original state when an operation fails.

## Build

Developed with:

- C++17 or later
- Visual Studio 2022

Open:

~~~text
Safe-Config-Loader.sln
~~~

and build the solution in Visual Studio.

## Purpose

This project is part of my C++ learning roadmap and focuses on writing safer APIs rather than only learning `try`, `catch`, and `throw` syntax.

The main goal was to understand how exception handling interacts with API design, abstraction boundaries, RAII, and program state.
