#include <Debug/Logger.hpp>

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/dist_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#if defined(_WIN32) || defined(_WIN64)
#include <spdlog/sinks/wincolor_sink.h>
#else
#include <spdlog/sinks/ansicolor_sink.h>
#endif

namespace jde::Debug
{
    Logger Log;
    void initLogger()
    {
        // Create sink distributor
        auto dist_sink = std::make_shared<spdlog::sinks::dist_sink_st>();

        // Create the 2 sinks
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_st>();
        auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/debug.log");

        // Append sinks to the distributor
        dist_sink->add_sink(console_sink);
        dist_sink->add_sink(file_sink);

        // Build and initialize the logger
        Log = std::make_shared<spdlog::logger>("Log", dist_sink);
        Log->set_pattern("[%H:%M:%S.%e]<%^%l%$> : %v");
        Log->set_level(spdlog::level::trace);
        Log->flush_on(spdlog::level::warn);
    }

    void trace(const std::string &msg)
    {
        Log->trace(msg);
    }

    void debug(const std::string &msg)
    {
        Log->debug(msg);
    }

    void info(const std::string &msg)
    {
        Log->info(msg);
    }

    void warn(const std::string &msg)
    {
        Log->warn(msg);
    }

    void error(const std::string &msg)
    {
        Log->error(msg);
    }

    void critical(const std::string &msg)
    {
        Log->critical(msg);
    }
} // namespace jde::Debug
