#pragma once
#include <iostream>
#include <fstream>
#include <mutex>
#include <shared_mutex>
#include <string>
#include <thread>



class Logger
{
private:
    std::ofstream file;
    mutable std::shared_mutex mutex;

public:
    Logger(const std::string& filename) : file(filename, std::ios_base::app), mutex()
    {
        if (!file.is_open())
        {
            file.open(filename);
        }
    }

    ~Logger()
    {
        if (file.is_open())
        {
            file.close();
        }
    }

    void writeLog(const std::string& message);

    std::string readLog() const;
};

