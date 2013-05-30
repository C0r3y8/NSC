#include "parser.h"

using namespace std;

/**
 * Parse type of query
 * @brief Parser::parseType
 * @param s
 * @return
 */
string Parser::parseType(string s) {
    if (s.size() != 0) {
        unsigned end = s.find_first_of(" ");

        string reqType;
        for (unsigned i = 0; i < end; i++) {
            reqType += s.at(i);
        }
        return reqType;
    } else {
        return "";
    }
}

/**
 * Parse query
 * @brief Parser::parseRequest
 * @param s
 * @return string (query)
 */
string Parser::parseQuery(string s) {
    if (s.size() != 0) {
        unsigned begin = s.find_first_of(" ");
        unsigned end = s.find_first_of(" ", begin+1);

        string query;
        for (unsigned i = (begin + 1); i < end; i++) {
            query +=  s.at(i);
        }

        return query;
    } else {
        return "";
    }
}

/**
 * Parse the name of the module and verifies it's a directory
 * @brief Parser::parseModule
 * @param request
 * @return string (name of module)
 */
string Parser::parseModule(string& request) {
    string name;
    int isDir;

    if (request.size() != 0) {
        if (request.size() == 1) {
            return "default";
        } else if (request.size() > 1) {
            unsigned begin = request.find_first_of("/");
            unsigned end = request.find_first_of("/", begin+1);
            if (end != string::npos) {
                for (unsigned i = (begin + 1); i < end; i++) {
                    first +=  request.at(i);
                    request.erase(i);
                }
                request.erase(end);
                isDir = FileProcessing::is_dir(name);
                if (isDir == 1) {
                    return name;
                } else if (isDir == 2) {
                    cerr << "Name of directory not allowed." << endl;
                    return "error";
                } else {
                    cerr << "Directory doesn't exist." << endl;
                    return "error";
                }
            }
        } else {
            return "error";
        }
    } else {
        return "error";
    }
}
