#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <vector>

enum class Color
{
    Red = 31,
    Green = 32,
    Yellow = 33,
    Cyan = 36
};

enum LogType
{
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR
};

struct MessageFormat
{
    Color color;
    LogType type;
    std::string StartLog;
};

struct LogEntry
{
    LogType type;
    std::string message;
};

class Logger
{
  public:
    static void Info(const std::string& message);
    static void Error(const std::string& description);
    static std::vector<LogEntry> messages;
    static std::string current_time();

  private:
    static void print_colored(const std::string& text, const MessageFormat& format);
};

#endif