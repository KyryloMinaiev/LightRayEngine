//
// Created by Kirill Minaev on 02.07.2024.
//

#ifndef LIGHTRAYENGINE_JSONLIBRARYEXCEPTION_H
#define LIGHTRAYENGINE_JSONLIBRARYEXCEPTION_H

#include <exception>
#include <string>

namespace JsonLibrary {
    class JsonLibraryException : public std::exception {
    public:
        explicit JsonLibraryException (const std::string &message) : exception() {
            m_message = message;
        }

        [[nodiscard]] const char *what() const _NOEXCEPT override {
            return m_message.c_str();
        }

    protected:
        std::string m_message;
    };
}

#endif //LIGHTRAYENGINE_JSONLIBRARYEXCEPTION_H
