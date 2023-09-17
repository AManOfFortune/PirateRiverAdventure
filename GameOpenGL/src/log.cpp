#include "log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

std::shared_ptr<spdlog::logger> Log::logger_;

void Log::Initialize()
{
    spdlog::set_pattern("%^[%T]: %v%$");
    logger_ = spdlog::stdout_color_mt("LOG");
    logger_->set_level(spdlog::level::trace);
}