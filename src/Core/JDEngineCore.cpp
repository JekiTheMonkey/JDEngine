#include <JDEngineCore.hpp>

#include <Debug/Logger.hpp>


namespace jde
{
    void initEngine()
    {
        Debug::initLogger();

        Debug::Log->debug("<JDEngine> Logger has been initialized.");

        // Debug::debug("<JDEngine> Initialising NullTexture.");
        // Graphics::MakeNullTexture();
    }
} // namespace jde
