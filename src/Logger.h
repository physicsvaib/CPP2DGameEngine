#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>

enum class Color
{
  Red = 31,
  Green = 32,
  Yellow = 33,
  Cyan = 36
};

struct MessageFormat
{
  Color color;
  std::string StartLog;
};

class Logger
{
public:
  static void Info(const std::string& message);
  static void Error(const std::string& description);

private:
  static std::string current_time();
  static void print_colored(const std::string& text, MessageFormat);
};

#endif