#include <Config/Config.hpp>
#include <System/Window.hpp>

#include <SFML/Graphics/Texture.hpp>


namespace jde::System
{
    Window::Window(const Config::ConfigurationManager &configuration)
    {
        // --- Window size

        unsigned int windowWidth = 0u;
        unsigned int windowHeight = 0u;
        
        if (auto widthPtr = configuration.get_if<unsigned int>(Config::Field::WindowWidth); widthPtr)
            windowWidth = *widthPtr;
        else
            windowWidth = m_width_;
        if (auto heightPtr = configuration.get_if<unsigned int>(Config::Field::WindowHeight); heightPtr)
            windowHeight = *heightPtr;
        else 
            windowHeight = m_height_;
        if (auto titlePtr = configuration.get_if<std::string>(Config::Field::Titlebar); titlePtr)
            m_title_ = *titlePtr;

        setSize(windowWidth, windowHeight);

        // --- Window style

        bool fullscreen = true;
        bool closeable = true;
        bool resizeable = true;
        bool titlebar = true;

        if (auto fullscreenPtr = configuration.get_if<bool>(Config::Field::Fullscreen); fullscreenPtr)
            fullscreen = *fullscreenPtr;
        if (auto closeablePtr = configuration.get_if<bool>(Config::Field::Closeable); closeablePtr)
            fullscreen = *closeablePtr;
        if (auto resizeablePtr = configuration.get_if<bool>(Config::Field::Resizeable); resizeablePtr)
            fullscreen = *resizeablePtr;
        if (auto titlebarPtr = configuration.get_if<bool>(Config::Field::Titlebar); titlebarPtr)
            fullscreen = *titlebarPtr;

        m_style_ = sf::Style::Default;
        if (fullscreen)
            m_style_ = sf::Style::Fullscreen;
        else
        {
            if (closeable)
                m_style_ |= sf::Style::Close;
            if (resizeable)
                m_style_ |= sf::Style::Resize;
            if (titlebar)
                m_style_ |= sf::Style::Titlebar;
        }

        // --- Window title

        m_title_ = "JDEngine";
        if (auto titlePtr = configuration.get_if<std::string>(Config::Field::WindowTitle); titlePtr)
            m_title_ = *titlePtr;
    }

    void Window::create()
    {
        m_window_.create(sf::VideoMode(m_width_, m_height_), m_title_, m_style_);
        m_window_.setKeyRepeatEnabled(false);

        applyView();
    }

    void Window::clear()
    {
        m_window_.clear();
    }

    void Window::close()
    {
        m_window_.close();
    }

    void Window::display()
    {
        m_window_.display();
    }

    void Window::draw(const sf::Drawable &drawable,
        const sf::RenderStates &states)
    {
        m_window_.draw(drawable, states);
    }

    void Window::draw(const sf::Vertex* vertices, std::size_t vertexCount, 
        sf::PrimitiveType type, const sf::RenderStates& states)
    {
        m_window_.draw(vertices, vertexCount, type, states);
    }

    sf::Vector2u Window::getSize() const
    {
        return m_window_.getSize();
    }

    bool Window::isOpen() const
    {
        return m_window_.isOpen();
    }

    bool Window::pollEvent(sf::Event &event)
    {
        return m_window_.pollEvent(event);
    }

    void Window::setSize(unsigned width, unsigned height)
    {
        m_window_.setSize(sf::Vector2u(width, height));
        setView(sf::View(sf::FloatRect(0.f, 0.f, width, height)));
        m_width_ = width;
        m_height_ = height;
        applyView();
    }

    void Window::setTitle(const std::string &title)
    {
        m_title_ = title;
        m_window_.setTitle(title);
    }

    void Window::setVerticalSyncEnabled(bool enabled)
    {
        m_window_.setVerticalSyncEnabled(enabled);
    }

    void Window::setView(const sf::View &view)
    {
        m_window_.setView(view);
    }

    void Window::setIcon(const std::string &path)
    {
        sf::Texture iconTexture;
        iconTexture.loadFromFile(path);
        m_icon_ = iconTexture.copyToImage();

        m_window_.setIcon(32, 32, m_icon_.getPixelsPtr());
    }

    void Window::applyView()
    {
        m_window_.setView(m_view_);
    }
} // namespace jde::System
