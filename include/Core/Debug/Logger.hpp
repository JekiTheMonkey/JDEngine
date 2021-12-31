#pragma once

#include <spdlog/spdlog.h>

#include <memory>


namespace jde::Debug
{
    using Logger = std::shared_ptr<spdlog::logger>;
    // Log is declared in Logger.cpp
    extern Logger Log;

    /// @brief Initialize the Logger
    void initLogger();

    void trace(const std::string &msg);
    void debug(const std::string &msg);
    void info(const std::string &msg);
    void warn(const std::string &msg);
    void error(const std::string &msg);
    void critical(const std::string &msg);
} // namespace jde::Debug
