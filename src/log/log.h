#pragma once

#include <string>
#include <source_location>

enum class LogLevel {INFO, DEBUG, WARNING, ERROR};


class Log{
public:
  Log() = delete;

  static void info(const std::string_view message, 
    const std::source_location location = std::source_location::current());
  
  static void debug(const std::string_view message,
    const std::source_location location = std::source_location::current());

  static void warning(const std::string_view message,
    const std::source_location location = std::source_location::current());

  static void error(const std::string_view message,
    const std::source_location location = std::source_location::current());

private:
  static void log(LogLevel logLevel,
      const std::string_view message,
      const std::source_location location);
};
