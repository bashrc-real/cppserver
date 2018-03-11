#ifndef custom_exception
#define custom_exception

#include <exception>
#include <string>

namespace cppserver{
    class HttpRequestException : std::exception{
    public:
        explicit HttpRequestException(const char* message):
            m_message(message), m_statusCode(500){
        }

        explicit HttpRequestException(const char* message, int statusCode):
        m_message(message), m_statusCode(statusCode)
        {
        }

        explicit HttpRequestException(const std::string& message):
        m_message(message), m_statusCode(500)
        {}

        virtual const char* what() const throw (){
            return m_message.c_str();
        }

        virtual ~HttpRequestException() throw (){}
        private:
            std::string m_message;
            int m_statusCode;  
    };

    class InvalidDataException : std::exception{
    public:
        virtual const char* what() const throw (){
            return m_message.c_str();
        }
        virtual ~InvalidDataException() throw (){}
        private:
            std::string m_message = "Invalid data supplied";
    };
}