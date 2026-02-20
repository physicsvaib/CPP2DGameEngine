
#include "Logger.h"
#include <ctime>
#include <iomanip>

MessageFormat error = {Color::Red, "Error"};
MessageFormat warning = {Color::Yellow, "Warning"};
MessageFormat info = {Color::Green, "Log"};

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
  std::time_t t = std::time(nullptr);
  std::tm* now = std::localtime(&t);

  std::ostringstream oss;
  oss << std::setfill('0') << std::setw(2) << now->tm_hour << ":" << std::setw(2) << now->tm_min
      << ":" << std::setw(2) << now->tm_sec;
  return oss.str();
}

void Logger::print_colored(const std::string& text, MessageFormat format)
{
  std::cout << "\033[" << static_cast<int>(format.color) << "m" << "[" << format.StartLog << " "
            << current_time() << "] " << text << "\033[0m" << std::endl;
}