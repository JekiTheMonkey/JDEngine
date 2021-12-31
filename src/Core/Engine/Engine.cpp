#include <Engine/Engine.hpp>
#include <Engine/Exceptions.hpp>


namespace jde::Engine
{
    void Engine::initConfig()
    {
    }

    void Engine::initLogger()
    {
    }

    void Engine::initScript()
    {
    }

    void Engine::initInput()
    {
    }

    void Engine::initFramerate()
    {
    }

    void Engine::initResources()
    {
    }

    void Engine::initWindow()
    {
    }

    void Engine::initScene()
    {
    }

    void Engine::handleWindowEvents()
    {
    }

    void Engine::update()
    {
    }

    void Engine::render()
    {
    }

    void Engine::clean()
    {
    }

    void Engine::purge()
    {
    }


    Engine::Engine()
    : m_log_(Debug::Log)
    {
    }

    Engine::~Engine()
    {
        Debug::debug("Engine has been correctly cleaned.");
    }

    void Engine::init()
    {
        initConfig();
        initLogger();
        initScript();
        initInput();
        initFramerate();
        initResources();
        initWindow();
        initScene();

        m_initialized = true;
    }

    void Engine::run()
    {
        if (!m_initialized)
            throw Exceptions::UnitializedEngine(EXC_INFO);
    }
} // namespace jde::Engine
