#include "log.h"
#include <iostream>
#include <string>

void Log::log(
    LogLevel logLevel, const std::string_view message, 
    const std::source_location location) 
{
  std::string logLevelString = "";
  switch (logLevel) {
    case LogLevel::INFO:
      logLevelString = "INFO";
      break;
    case LogLevel::DEBUG:
      logLevelString = "WARNING";
      break;
    case LogLevel::WARNING:
      logLevelString = "WARNING";
      break;
    case LogLevel::ERROR:
      logLevelString = "ERROR";
      break;
  }
  std::cout << logLevelString << location.file_name() << " : " << location.line() << message << '\n';
}

void Log::info(
    const std::string_view message,
    const std::source_location location) 
{
  Log::log(LogLevel::INFO, message, location);
}

void Log::debug(
    const std::string_view message,
    const std::source_location location) 
{
  Log::log(LogLevel::DEBUG, message, location);
}

void Log::warning(
    const std::string_view message,
    const std::source_location location) 
{
  Log::log(LogLevel::WARNING, message, location);
}

void Log::error(
    const std::string_view message,
    const std::source_location location) 
{
  Log::log(LogLevel::ERROR, message, location);
}