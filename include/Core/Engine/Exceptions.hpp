#pragma once

#include <Exception.hpp>


namespace jde::Engine::Exceptions
{
    class UnitializedEngine : public Exception<UnitializedEngine>
    {
    public:
        using Exception::Exception;
        UnitializedEngine(DebugInfo info)
        : Exception(info)
        {
            error("Impossible to run Engine if not initialized beforehand.");
        }
    };

    class TextureNotFoundOnAcquire : public Exception<TextureNotFoundOnAcquire>
    {
    public:
        using Exception::Exception;
        TextureNotFoundOnAcquire(std::string_view path, DebugInfo info)
        : Exception(info)
        {
            error(fmt::format("Could not load Texture with path '{}'.", path));
        }
    };

    class TextureIdAlreadyUsed : public Exception<TextureIdAlreadyUsed>
    {
    public:
        using Exception::Exception;
        TextureIdAlreadyUsed(std::string_view path, std::string_view id, DebugInfo info)
        : Exception(info)
        {
            error(fmt::format("Could not load Texture with path '{}' with ID '{}'. "
                "The ID is already occupied.", path, id));
        }
    };

    class TextureNotFoundOnGet : public Exception<TextureNotFoundOnGet>
    {
    public:
        using Exception::Exception;
        TextureNotFoundOnGet(std::string_view id, DebugInfo info)
        : Exception(info)
        {
            error(fmt::format("Could not find Texture with ID '{}'.", id));
        }
    };

    class FontNotFoundOnAcquire : public Exception<FontNotFoundOnAcquire>
    {
    public:
        using Exception::Exception;
        FontNotFoundOnAcquire(std::string_view path, DebugInfo info)
        : Exception(info)
        {
            error(fmt::format("Could not find Font with path '{}'.", path));
        }
    };

    class FontNotFoundOnGet : public Exception<FontNotFoundOnGet>
    {
    public:
        using Exception::Exception;
        FontNotFoundOnGet(std::string_view id, DebugInfo info)
        : Exception(info)
        {
            error(fmt::format("Could not find Font with ID '{}'.", id));
        }
    };

    class FontIdAlreadyUsed : public Exception<FontIdAlreadyUsed>
    {
    public:
        using Exception::Exception;
        FontIdAlreadyUsed(std::string_view path, std::string_view id, DebugInfo info)
        : Exception(info)
        {
            error(fmt::format("Could not load Font with path '{}' with ID '{}'. "
                "The ID is already occupied.", path, id));
        }
    };
} // namespace jde::Engine
