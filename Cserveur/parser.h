#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <map>

#include "fileprocessing.h"

/**
 * Parser
 * @author Stéphane Barale <stephane.barale@gmail.com>
 * @brief The Parser class
 * @since v0.2
 */
class Parser{
    public:
        Parser() {}
        virtual ~Parser() {}
        static std::string parseType(std::string);
        static std::string parseQuery(std::string);
        static std::string parseModule(std::string);
        static std::string parsePage(std::string);
        static std::map<std::string, std::string> parseParams(std::string);
};

#endif // PARSER_H
