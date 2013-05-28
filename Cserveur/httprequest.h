#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <string.h>
#include <stdio.h>
#include <iostream>
/**
 *
 * @brief The HTTPRequest class
 * @since v0.2
 */
class HTTPRequest {
    public:
        HTTPRequest(std::string);
        ~HTTPRequest();
        bool isValid();
        void setValid(bool);
        std::string parseType(std::string);
        std::string parseRequest(std::string);
        std::string getRequest();
        std::string getType();
    private:
        std::string request;
        std::string type;
        bool valid;
};

#endif // HTTPREQUEST_H
