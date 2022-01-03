#include <Debug/Logger.hpp>
#include <Engine/ResourceManager.hpp>
#include <Engine/Exceptions.hpp>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>


namespace jde::Engine
{
    ResourceManager::ResourceManager() = default;
    ResourceManager::~ResourceManager() = default;

    void ResourceManager::acquireFont(const std::string &id, const std::string &path)
    {
        Debug::Log->debug("<ResourceManager> Loading <Font> '{}' from '{}'", id, path);

        // Create uptr for the resource, try to load from file
        auto resource = std::make_unique<sf::Font>();
        if (!resource->loadFromFile(path))
            throw Exceptions::FontNotFoundOnAcquire(path, EXC_INFO);

        Debug::Log->debug("<ResourceManager> Inserting <Font> '{}' from '{}'", id, path);

        // Try to insert the resource, control the success
        auto inserted = m_fonts_.insert(std::make_pair(id, std::move(resource)));
        if (!inserted.second)
            throw Exceptions::FontIdAlreadyUsed(path, id, EXC_INFO);
    }

    void ResourceManager::acquireTexture(const std::string &id, const std::string &path)
    {
        Debug::Log->debug("<ResourceManager> Loading <Texture> '{}' from '{}'", id, path);

        // Create uptr for the resource, try to load from file
        auto resource = std::make_unique<sf::Texture>();
        if (!resource->loadFromFile(path))
            throw Exceptions::TextureNotFoundOnAcquire(path, EXC_INFO);

        Debug::Log->debug("<ResourceManager> Inserting <Texture> '{}' from '{}'", id, path);
        
        // Try to insert the resource, control the success
        auto inserted = m_textures_.insert(std::make_pair(id, std::move(resource)));
        if (!inserted.second)
            throw Exceptions::TextureIdAlreadyUsed(path, id, EXC_INFO);
    }

    void ResourceManager::releaseFont(const std::string &id)
    {
        Debug::Log->debug("<ResourceManager> Releasing <Font> '{}'.", id);
        
        if (!m_fonts_.erase(id))
            throw Exceptions::FontNotFoundOnGet(id, EXC_INFO);
    }

    void ResourceManager::releaseTexture(const std::string &id)
    {
        Debug::Log->debug("<ResourceManager> Releasing <Texture> '{}'.", id);

        if (!m_textures_.erase(id))
            throw Exceptions::TextureNotFoundOnGet(id, EXC_INFO);
    }

    const sf::Font &ResourceManager::getFont(const std::string &id) const
    {
        // Try to find the resource, control the success
        auto found = m_fonts_.find(id);
        if (found == m_fonts_.end())
            throw Exceptions::FontNotFoundOnGet(id, EXC_INFO);

        // Return if found
        return *found->second;
    }

    sf::Font &ResourceManager::getFont(const std::string &id)
    {
        return const_cast<sf::Font&>(
            static_cast<const ResourceManager&>(*this).getFont(id));
    }

    const sf::Texture &ResourceManager::getTexture(const std::string &id) const
    {
        // Try to find the resource, control the success
        auto found = m_textures_.find(id);
        if (found == m_textures_.end())
            throw Exceptions::TextureNotFoundOnGet(id, EXC_INFO);

        // Return if found
        return *found->second;
    }

    sf::Texture &ResourceManager::getTexture(const std::string &id)
    {
        return const_cast<sf::Texture&>(
            static_cast<const ResourceManager&>(*this).getTexture(id));
    }
} // namespace jde::Engine
