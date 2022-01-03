#pragma once

#include <Exception.hpp>

#include <vector>


namespace jde::Config::Exceptions
{
    class ConfigError : public Exception<ConfigError>
    {
    public:
        using Exception::Exception;
        ConfigError(DebugInfo info)
        : Exception(info)
        {
            error("'config.lua' read from 'engine/confia.lua' is malformed.");
        }
    };

    class NonExistingObject : public Exception<NonExistingObject>
    {
    public:
        using Exception::Exception;
        NonExistingObject(std::string_view objectName, DebugInfo info)
        : Exception(info)
        {
            error(fmt::format("Object '{}' does not exist.", objectName));
        }
    };

    class InvalidType : public Exception<InvalidType>
    {
    public:
        using Exception::Exception;
        InvalidType(std::string_view objectName, std::string_view type, DebugInfo info)
        : Exception(info)
        {
            error(fmt::format("Object '{}' is not of type '{}'.", objectName, type));
        }
    };
} // namespace jde::Config::Exceptions
