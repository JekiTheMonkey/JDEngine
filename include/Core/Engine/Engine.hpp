#pragma once

#include <Config/ConfigFwd.hpp>
#include <Debug/Logger.hpp>
#include <Engine/ResourceManagerFwd.hpp>
#include <System/WindowFwd.hpp>

#include <SFML/System/NonCopyable.hpp>


namespace jde::Engine
{
    class Engine : private sf::NonCopyable
    {
    public:
        Engine();
        ~Engine();

        void init();
        void run();

        // *getters*


    protected:
        // Initialization
        void initConfig();
        void initLogger();
        void initScript();
        void initInput();
        void initFramerate();
        void initResources();
        void initWindow();
        void initScene();

        // Main loop
        void handleWindowEvents();
        void update();
        void render();

        // Cleaning
        void clean();
        void purge();


    protected:
        bool m_initialized = false;
        // *all the uptrs to some basic stuff*
        Debug::Logger::weak_type m_log_;

        // *all the uptrs to resource managers*
        std::unique_ptr<Config::ConfigurationManager> m_config_;
        std::unique_ptr<System::Window> m_window_;
        std::unique_ptr<ResourceManager> m_resources_;
    };
} // namespace jde::Engine
