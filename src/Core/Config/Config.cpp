#include <Config/Config.hpp>
#include <Config/Exceptions.hpp>

/*
 * ConfigManager - Tasks
 * - Open the config
 * - Read the config
 * - Validate the read data
 * 
 * When the program is about it finish
 * - Open the config
 * - Write new data (even if it the same)
*/

namespace jde::Config
{
    unsigned int strToLogLevel(std::string_view string)
    {
        if (string == "Trace")
            return spdlog::level::trace;
        else if (string == "Debug")
            return spdlog::level::debug;
        else if (string == "Info")
            return spdlog::level::info;
        else if (string == "Warn")
            return spdlog::level::warn;
        else if (string == "Err")
            return spdlog::level::err;
        else if (string == "Critical")
            return spdlog::level::critical;
        else if (string == "Off")
            return spdlog::level::off;
        else
        {
            Debug::Log->warn("<Configuration> Log level '{}' "
                "does not exist, 'Warn' level will be used instead. "
                "", string);
            return spdlog::level::warn;
        }
    }

    void ConfigurationManager::load()
    {
        const std::string filepath = "engine/config.lua";

        // Create LVM
        sol::state lua;

        // Open config file, control the result
        const auto loadResult = lua.safe_script_file(filepath);
        if (!loadResult.valid())
        {
            const auto errObj = loadResult.get<sol::error>();
            throw Exceptions::ConfigError(EXC_INFO);
        }

        // Copy config table, control if it did
        sol::optional<sol::table> configOpt = lua["Config"];
        if (!configOpt.has_value())
            throw Exceptions::ConfigError(EXC_INFO);
        
        // Use dereferenced version instead
        const auto &config = *configOpt;

        // --- Parameters reading

        #define WARN_MISSING_PARAMETER(x) Debug::warn(fmt::format("<Configuration> Warning: '{}' is missing.", #x));

        // Framerate
        if (sol::optional<sol::table> framerate = config["Framerate"]; 
            framerate.has_value())
        {
            // FramerateTarget
            if (sol::optional<unsigned int> framerateTarget = (*framerate)["framerateTarget"]; 
                framerateTarget.has_value())
            {
                m_config_.insert(std::make_pair(Field::FramerateTarget, *framerateTarget));
            }
            else
                WARN_MISSING_PARAMETER(framerateTarget)

            // Vsync
            if (sol::optional<bool> vsync = (*framerate)["vsync"]; 
                vsync.has_value())
            {
                m_config_.insert(std::make_pair(Field::Vsync, *vsync));
            }
            else
                WARN_MISSING_PARAMETER(vsync)
        }
        else
            WARN_MISSING_PARAMETER(framerate)

        // Window
        if (sol::optional<sol::table> window = config["Window"]; 
            window.has_value())
        {
            // Fullscreen
            if (sol::optional<bool> fullscreen = (*window)["fullscreen"]; 
                fullscreen.has_value())
            {
                m_config_.insert(std::make_pair(Field::Fullscreen, *fullscreen));
            }
            else
                WARN_MISSING_PARAMETER(fullscreen)

            // Closeable
            if (sol::optional<bool> closeable = (*window)["closeable"]; 
                closeable.has_value())
            {
                m_config_.insert(std::make_pair(Field::Closeable, *closeable));
            }
            else
                WARN_MISSING_PARAMETER(closeable)

            // Resizeable
            if (sol::optional<bool> resizeable = (*window)["resizeable"]; 
                resizeable.has_value())
            {
                m_config_.insert(std::make_pair(Field::Resizeable, *resizeable));
            }
            else
                WARN_MISSING_PARAMETER(resizeable)

            // Titlebar
            if (sol::optional<bool> titlebar = (*window)["titlebar"]; 
                titlebar.has_value())
            {
                m_config_.insert(std::make_pair(Field::Titlebar, *titlebar));
            }
            else
                WARN_MISSING_PARAMETER(titlebar)

            // Width
            if (sol::optional<unsigned int> width = (*window)["width"]; 
                width.has_value())
            {
                m_config_.insert(std::make_pair(Field::WindowWidth, *width));
            }
            else
                WARN_MISSING_PARAMETER(width)

            // Height
            if (sol::optional<unsigned int> height = (*window)["height"]; 
                height.has_value())
            {
                m_config_.insert(std::make_pair(Field::WindowHeight, *height));
            }
            else
                WARN_MISSING_PARAMETER(height)

            // Title
            if (sol::optional<std::string> title = (*window)["title"]; 
                title.has_value())
            {
                m_config_.insert(std::make_pair(Field::WindowTitle, *title));
            }
            else
                WARN_MISSING_PARAMETER(title)
        }
        else
            WARN_MISSING_PARAMETER(window)

        // Debug
        if (sol::optional<sol::table> debug = config["Debug"]; 
            debug.has_value())
        {
            // Logging
            if (sol::optional<sol::table> logging = (*debug)["Logging"]; 
                logging.has_value())
            {
                // Level
                if (sol::optional<std::string> level = (*logging)["level"];
                    level.has_value())
                { 
                    m_config_.insert(std::make_pair(Field::LoggingLevel, strToLogLevel(*level)));
                }
                else
                    WARN_MISSING_PARAMETER(level)
            }
            else
                WARN_MISSING_PARAMETER(logging)
        }
        else
            WARN_MISSING_PARAMETER(debug)

        #undef VALUE_ERROR_CHECK
    }

    bool ConfigurationManager::contains(Field key) const
    {
        return m_config_.contains(key);
    }
    
    std::string parToStr(Field parameter)
    {
        switch (parameter)
        {
            case Field::FramerateTarget: return "FramerateTarget";
            case Field::Vsync: return "Vsync";
            case Field::Fullscreen: return "Fullscreen";
            case Field::Closeable: return "Closeable";
            case Field::Resizeable: return "Resizeable";
            case Field::Titlebar: return "Titlebar";
            case Field::WindowWidth: return "WindowWidth";
            case Field::WindowHeight: return "WindowHeight";
            case Field::WindowTitle: return "WindowTitle";
            case Field::LoggingLevel: return "LoggingLevel";
            default: return "null";
        }
    }
} // namespace jde::Config
