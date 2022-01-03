#include <Config/Config.hpp>
#include <Engine/Engine.hpp>
#include <Engine/Exceptions.hpp>


namespace jde::Engine
{
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

    void Engine::initConfig()
    {
        m_config_ = std::make_unique<Config::ConfigurationManager>();
        m_config_->load();
    }

    void Engine::initLogger()
    {
        if (m_config_->contains(Config::Field::LoggingLevel))
        {
            const auto logLevel = m_config_->at<unsigned int>(Config::Field::LoggingLevel);
            const auto level = static_cast<spdlog::level::level_enum>(logLevel);
            Debug::Log->set_level(level);
            Debug::Log->info("Log Level is set to '{}'", logLevel);
        }
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
} // namespace jde::Engine
