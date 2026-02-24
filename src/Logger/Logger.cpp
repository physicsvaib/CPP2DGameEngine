#include "Logger.h"
#include <ctime>
#include <iostream>

// Define message formats
MessageFormat error = {Color::Red, LOG_ERROR, "Error"};
MessageFormat warning = {Color::Yellow, LOG_WARNING, "Warning"};
MessageFormat info = {Color::Green, LOG_INFO, "Info"};

std::vector<LogEntry> Logger::messages;

void Logger::Info(const std::string& message)
{
    print_colored(message, info);
}

void Logger::Error(const std::string& description)
{
    print_colored(description, error);
}

std::string Logger::current_time()
{
    time_t t = time(nullptr);
    struct tm* now = localtime(&t);
    std::string buffer(32, '\0');
    strftime(&buffer[0], sizeof(buffer), "%d-%b-%Y %H:%M:%S", now);
    return std::string(buffer);
}

void Logger::print_colored(const std::string& text, const MessageFormat& format)
{
    LogEntry entry;
    entry.type = format.type;
    entry.message = "[" + format.StartLog + " " + current_time() + "] " + text;
    messages.push_back({format.type, text});
    std::cout << "\033[" << static_cast<int>(format.color) << "m" << entry.message << "\033[0m"
              << std::endl;
}
