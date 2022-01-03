#pragma once

#include <Config/Exceptions.hpp>

#include <sol/sol.hpp>

#include <string>
#include <map>
#include <variant>


namespace jde::Config
{
    enum class Field
    {
        FramerateTarget,
        Vsync, 
        Fullscreen,
        Closeable,
        Resizeable,
        Titlebar,
        WindowWidth,
        WindowHeight,
        WindowTitle,
        LoggingLevel
    };

    /// @brief Class to store configuration
    /// @details The class stores and provides JDE configuration data as they must be.
    /// If a parameter in config is malformed - it will not be stored by the config.
    class ConfigurationManager
    {
        public:


        public:
            void load();

            template <typename T>
            T at(Field parameter);
            template <typename T>
            const T *get_if(Field parameter) const;
            template <typename T>
            T *get_if(Field parameter);
            bool contains(Field parameter) const;


        private:
            using Object = std::variant<unsigned int, int, bool, float, std::string>;

        
        private:
            std::map<Field, Object> m_config_;
    };

    std::string parToStr(Field parameter);

    template <typename T>
    T ConfigurationManager::at(Field key)
    {
        // Try to get the object, control if it was found
        auto found = m_config_.find(key);
        if (found == m_config_.end())
            throw Exceptions::NonExistingObject(EXC_INFO, parToStr(key));

        // Control if variant holds the right object type
        if (const auto tPtr(std::get_if<T>(&found->second)); tPtr)
        {
            // Return if it does
            return *tPtr;
        }
        else
        {
            const auto stringPassedType = getTypeName<T>();
            throw Exceptions::InvalidType(EXC_INFO, parToStr(key), stringPassedType);
        }
    }

    template <typename T>
    const T *ConfigurationManager::get_if(Field key) const
    {
        // Try to get the object, control if it was found
        auto found = m_config_.find(key);
        if (found == m_config_.end())
            throw Exceptions::NonExistingObject(EXC_INFO, parToStr(key));

        // Return the pointer to the object if it everything is right, otherwise nullptr
        return std::get_if<T>(&found->second);
    }

    template <typename T>
    T *ConfigurationManager::get_if(Field key)
    {
        return const_cast<T*>(
            static_cast<const ConfigurationManager>(*this).get_if<T>(key));
    }
} // namespace jde::Config
