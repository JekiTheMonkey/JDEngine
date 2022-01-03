#include <JDEngineCore.hpp>
#include <Engine/Engine.hpp>

#include <iostream>
#include <stdexcept>


int main(int, char**)
{
    using namespace jde;

    try
    {
        initEngine();
    }
    catch(const std::exception &e)
    {
        Debug::Log->error(e.what());
        Debug::Log->error("Error occurred while initializing JDEngine");
        return 1;
    }

    try
    {
        Engine::Engine engine;
        engine.init();
        engine.run();
    }
    catch (const std::exception &e)
    {
        if (Debug::Log)
        {
            Debug::Log->error("The following error occurred while running JDEngine");
            Debug::Log->error(e.what());
        }
        else
        {
            std::cerr << "The following error occurred while running JDEngine" << std::endl;
            std::cerr << e.what() << std::endl;
        }

        return 1;
    }

    return 0;
}
