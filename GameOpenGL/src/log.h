#pragma once 

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

#include <memory.h>

/// <summary>
/// A wrapper class for the spdlog library. The static logger_ should only be instantiated once.
/// Use the logging macros instead of this class!
/// </summary>
class Log
{
public:
    /// <summary>
    /// Initializes the static logger singleton. Should only be called once.
    /// </summary>
    static void Initialize();

    /// <summary>
    /// Getter for the static logger singleton. Use the logging macros instead!
    /// </summary>
    inline static std::shared_ptr<spdlog::logger>& Logger() { return logger_; }

private:
    static std::shared_ptr<spdlog::logger> logger_;
};

// ---- Logging macros -------------------------------------------
#define LOG_TRACE(...)    ::Log::Logger()->trace(__VA_ARGS__)
#define LOG_DEBUG(...)    ::Log::Logger()->debug(__VA_ARGS__)
#define LOG_INFO(...)     ::Log::Logger()->info(__VA_ARGS__)
#define LOG_WARN(...)     ::Log::Logger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)    ::Log::Logger()->error(__VA_ARGS__)
#define LOG_CRITICAL(...) ::Log::Logger()->critical(__VA_ARGS__)
// ---------------------------------------------------------------