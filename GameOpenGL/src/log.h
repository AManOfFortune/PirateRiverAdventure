#pragma once 

#include "spdlog/spdlog.h"

#include <memory.h>

class Log
{
public:
    static void Initialize();

    inline static std::shared_ptr<spdlog::logger>& Logger() { return logger_; }

private:
    static std::shared_ptr<spdlog::logger> logger_;
};

// Logging macros
#define LOG_TRACE(...)    ::Log::Logger()->trace(__VA_ARGS__)
#define LOG_DEBUG(...)    ::Log::Logger()->debug(__VA_ARGS__)
#define LOG_INFO(...)     ::Log::Logger()->info(__VA_ARGS__)
#define LOG_WARN(...)     ::Log::Logger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)    ::Log::Logger()->error(__VA_ARGS__)
#define LOG_CRITICAL(...) ::Log::Logger()->critical(__VA_ARGS__)