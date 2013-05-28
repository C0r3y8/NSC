#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <string.h>
#include <stdio.h>
#include <iostream>
/**
 *  Parse module, page and type of request
 *
 * @author Stéphane Barale <stephane.barale@gmail.com>
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
