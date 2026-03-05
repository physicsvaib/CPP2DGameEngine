#include "Logger.h"
#include <ctime>
#include <iostream>

// Define message formats
MessageFormat error = {Color::Red, LOG_ERROR, "Error"};
MessageFormat warning = {Color::Yellow, LOG_WARNING, "Warning"};
MessageFormat info = {Color::Green, LOG_INFO, "Info"};
MessageFormat logPhyw = {Color::Cyan, LOG_LOG, "Log"};

std::vector<LogEntry> Logger::messages;

void Logger::Info(const std::string& message)
{
    PrintColored(message, info);
}

void Logger::Error(const std::string& description)
{
    PrintColored(description, error);
}

void Logger::Warning(const std::string& description)
{
    PrintColored(description, warning);
}

void Logger::Log(const std::string& description)
{
    PrintColored(description, logPhyw);
}

std::string Logger::CurrentTime()
{
    time_t t = time(nullptr);
    struct tm* now = localtime(&t);
    std::string buffer(32, '\0');
    strftime(&buffer[0], sizeof(buffer), "%d-%b-%Y %H:%M:%S", now);
    return std::string(buffer);
}

void Logger::PrintColored(const std::string& text, const MessageFormat& format)
{
    LogEntry entry;
    entry.type = format.type;
    entry.message = "[" + format.StartLog + " " + CurrentTime() + "] " + text;
    messages.push_back({format.type, text});
    std::cout << "\033[" << static_cast<int>(format.color) << "m" << entry.message << "\033[0m"
              << std::endl;
}
