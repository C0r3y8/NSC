#ifndef HTTPQUERY_H
#define HTTPQUERY_H

#include <string.h>
#include <stdio.h>
#include <iostream>
#include <map>

#include "parser.h"

/**
 *  Contain informations of query
 * @author Stéphane Barale <stephane.barale@gmail.com>
 * @brief The HTTPQuery class
 * @since v0.2
 */
class HTTPQuery {
    public:
        HTTPQuery(std::string);
        ~HTTPQuery();
        std::string getType();
        std::string getModule();
        std::string getPage();
        std::map<std::string, std::string> getParams();

    private:
        std::string module;
        std::string page;
        std::map<std::string, std::string> params;
        std::string type;
};

#endif // HTTPQUERY_H
