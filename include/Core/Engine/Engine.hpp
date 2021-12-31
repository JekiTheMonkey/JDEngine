#pragma once

#include <SFML/System/NonCopyable.hpp>

#include <Debug/Logger.hpp>


namespace jde::Engine
{
    class Engine : private sf::NonCopyable
    {
    protected:
        bool m_initialized = false;
        // *all the uptrs to some basic stuff*
        Debug::Logger::weak_type m_log_;

        // *all the uptrs to resource managers*

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


    public:
        Engine();
        ~Engine();

        void init();
        void run();

        // *getters*
    };
} // namespace jde::Engine
