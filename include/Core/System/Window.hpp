#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include <string>


namespace jde::Config
{
    class ConfigurationManager;
} // namespace jde::Config


namespace jde::System
{
    class Window
    {
    public:
        explicit Window(const Config::ConfigurationManager &configuration);
        void create();
        void clear();
        void close();
        void display();

        void draw(const sf::Drawable &drawable,
            const sf::RenderStates &states = sf::RenderStates::Default);

        void draw(const sf::Vertex* vertices, std::size_t vertexCount, sf::PrimitiveType type,
            const sf::RenderStates& states = sf::RenderStates::Default);

        sf::Vector2u getSize() const;
        bool isOpen() const;
        bool pollEvent(sf::Event &event);
        void setSize(unsigned width, unsigned height);
        void setTitle(const std::string &title);
        void setVerticalSyncEnabled(bool enabled);
        void setView(const sf::View &view);
        void setIcon(const std::string &path);

        sf::RenderWindow &getWindow();

        void setMouseCursorVisible(bool visible);

    private:
        void applyView();


    private:
        unsigned int m_width_ = 1920u;
        unsigned int m_height_ = 1080u;
        sf::Int32 m_style_;
        std::string m_title_ = "JDEngine";
        sf::RenderWindow m_window_;
        sf::View m_view_;
        sf::Image m_icon_;
        sf::Color m_background_ = sf::Color(0, 0, 0, 0);
    };
} // namespace jde::System
