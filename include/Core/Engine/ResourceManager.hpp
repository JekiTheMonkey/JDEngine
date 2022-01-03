#pragma once

#include <memory>
#include <unordered_map>


// Forward declarations
namespace sf
{
    class Font;
    class Texture;
} // namespace sf


namespace jde::Engine
{
    template <typename T>
    using ResourceStore = std::unordered_map<std::string, T>;
    
    /// @brief Class that manages and caches textures
    class ResourceManager
    {
    public:
        // Default ctor and dtor are required because Font and Texture are fwded in the header file
        ResourceManager();
        ~ResourceManager();


        /// @brief Loads a font with a given ID at a given path.
        /// @param id Identifier to use in methods to specify a font to act on.
        /// @param path Path of the font file to load.
        void acquireFont(const std::string &id, const std::string &path);

        /// @brief Loads a texture with a given ID at a given path.
        /// @param id Identifier to use in methods to specify a texture to act on.
        /// @param path Path of the texture file to load.
        void acquireTexture(const std::string &id, const std::string &path);


        /// @brief Removes a font associated with a given identifier.
        /// @param id Identifier of the font to remove.
        void releaseFont(const std::string &id);

        /// @brief Removes a texture associated with a given identifier.
        /// @param id Identifier of the texture to remove.
        void releaseTexture(const std::string &id);


        /// @brief Retrieves a font associated with a given identifier.
        /// @param id Identifier of the font to retrieve.
        const sf::Font &getFont(const std::string &id) const;

        /// @brief Retrieves a font associated with a given identifier.
        /// @param id Identifier of the font to retrieve.
        sf::Font &getFont(const std::string &id);

        /// @brief Retrieves a texture associated with a given identifier.
        /// @param id Identifier of the texture to retrieve.
        const sf::Texture &getTexture(const std::string &id) const;

        /// @brief Retrieves a texture associated with a given identifier.
        /// @param id Identifier of the texture to retrieve.
        sf::Texture &getTexture(const std::string &id);
        

    private:
        ResourceStore<std::unique_ptr<sf::Font>> m_fonts_;
        ResourceStore<std::unique_ptr<sf::Texture>> m_textures_;
    };
} // namespace jde::Engine
