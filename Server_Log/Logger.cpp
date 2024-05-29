#include "Logger.h"

void Logger::writeLog(const std::string& message)
{
    std::unique_lock<std::shared_mutex> lock(mutex);

    if (!file.is_open())
    {
        std::cerr << "Failed to open log file." << "\n";
        return;
    }

    file << message << "\n";

    file.close();
}

std::string Logger::readLog() const
{
    std::shared_lock<std::shared_mutex> lock(mutex);

    std::ifstream logFile("log.txt");

    if (logFile.fail())
    {
        std::cerr << "Failed to open log file." << "\n";
        return "";
    }

    if (logFile.is_open())
    {
        std::string line;
        std::string lastLine;

        while (getline(logFile, line))
        {
            lastLine = line;
        }

        logFile.close();

        return lastLine;
    }
    else
    {
        return "";
    }
}