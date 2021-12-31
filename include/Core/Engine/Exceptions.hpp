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
} // namespace jde::Engine
