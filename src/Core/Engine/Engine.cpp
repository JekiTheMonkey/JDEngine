#include <Config/Config.hpp>
#include <Engine/Engine.hpp>
#include <Engine/Exceptions.hpp>
#include <Engine/ResourceManager.hpp>
#include <System/Window.hpp>

#include <SFML/Window/Event.hpp>


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

        m_window_->create();

        while (m_window_->isOpen())
        {
            update();
        }
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
        m_resources_ = std::make_unique<ResourceManager>();
    }

    void Engine::initWindow()
    {
        Debug::Log->debug("<Engine> Window configuration");
        m_window_ = std::make_unique<System::Window>(*m_config_);
    }

    void Engine::initScene()
    {
    }

    void Engine::handleWindowEvents()
    {
        sf::Event event;
        while (m_window_->pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                m_window_->close();
                break;
            case sf::Event::Resized:
                m_window_->setSize(event.size.width, event.size.height);
                break;
            case sf::Event::KeyPressed:
                // input require refresh
                break;
            
            default:
                break;
            }
        }
    }

    void Engine::update()
    {
        handleWindowEvents();

        // other updates
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
