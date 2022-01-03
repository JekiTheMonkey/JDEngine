#pragma once

#include <Debug/Logger.hpp>

#include <fmt/core.h>

#include <exception>
#include <string>


namespace jde
{
    /// @brief Wrapper class containing information about the place that threw an exception.
    struct DebugInfo
    {
        std::string_view filename;
        int line;
        std::string_view funcname;

        DebugInfo(std::string_view _filename, int _line, std::string_view _funcname)
        : filename(_filename)
        , line(_line)
        , funcname(_funcname)
        {
        }
    };

#define EXC_INFO_WRAPPER() DebugInfo(__FILE__, __LINE__, __func__)
#define EXC_INFO EXC_INFO_WRAPPER()

#define OBJECT_NAME(x) #x

    template <typename T>
    constexpr auto getTypeName() -> std::string_view
    {
        // Define prefix and suffix of the __PRETTY_FUNCTION__ used in a compiler 
        // and get the whole function signature
#ifdef __clang__
        constexpr auto prefix = std::string_view { "[T = " };
        constexpr auto suffix = "]";
        constexpr auto function = std::string_view { __PRETTY_FUNCTION__ };
#elif __GNUC__
        constexpr auto prefix = std::string_view { "with T = " };
        constexpr auto suffix = "; ";
        constexpr auto function = std::string_view { __PRETTY_FUNCTION__ };
#elif _MSC_VER
        constexpr auto prefix = std::string_view { "getTypeName<" };
        constexpr auto suffix = ">(void)";
        constexpr auto function = std::string_view { __FUNCSIG__ };
#else
#error Unsupported compiler
#endif
        // Find the index where the type name starts and ends
        const auto start = function.find(prefix) + prefix.size();
        const auto end = function.find(suffix);

        // Calculate the length of the type word
        const auto size = end - start;

        // Return the substr indicating the type
        return function.substr(start, size);
    }


    /// @brief Wrapper class containing the information about the exception. 
    /// It's capable of adding fmt formatted messages to the details. 
    class BaseException : public std::exception
    {
    public:
        BaseException() = default;
        explicit BaseException(const std::exception &e) noexcept;

        /// @brief Records the error message. Supports fmt format.
        template <class... Args>
        void error(Args&&... args);
        /// @brief Records the hint message. Supports fmt format.
        template <class... Args>
        void hint(Args&&... args);
        /// @brief Returns the explanatory message.
        const char *what() const noexcept override;

    protected:
        std::string m_message_;
    };

    inline BaseException::BaseException(const std::exception &e) noexcept
    : m_message_(e.what())
    {
    }

    template <class... Args>
    void BaseException::error(Args&&... args)
    {
        // Append error message to the string
        m_message_ += fmt::format("  Error: {}", std::forward<Args>(args)...);

        // Output the error to standard error stream if logger is not initialized
        if (!Debug::Log)
            fprintf(stderr, "%s", m_message_.c_str());
    }

    template <class... Args>
    void BaseException::hint(Args&&... args)
    {
        // Append hint message to the string
        m_message_ += fmt::format("  Hint: {}\n", std::forward<Args>(args)...);
    }

    inline const char *BaseException::what() const noexcept
    {
        return m_message_.c_str();
    }


    /// @brief A base wrapper class containing the information about the 
    /// exception. It's capable of adding fmt formatted messages to it 
    /// and to define where the error occured. 
    template <class ExceptionType>
    class Exception : public BaseException
    {
    public:
        using BaseException::BaseException;
        explicit Exception(DebugInfo info);
    };

    template <class ExceptionType>
    Exception<ExceptionType>::Exception(DebugInfo info)
    {
        m_message_ = fmt::format("Exception [{}] occured\n", getTypeName<ExceptionType>());
#ifdef _DEBUG
        m_message_ += fmt::format("  In file: '{}' (line {})\n", info.filename, info.line);
        m_message_ += fmt::format("  In function: {}\n", info.funcname);
#endif
    }
} // namespace jde
