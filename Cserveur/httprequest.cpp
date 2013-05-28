#include "httprequest.h"

using namespace std;

/**
 * Constructor
 * @brief HTTPRequest::HTTPRequest
 * @param c
 */
HTTPRequest::HTTPRequest(string s) {
    type = parseType(s);
    request = parseRequest(s);
    s.erase();
}

/**
 * Defined if the request is valid
 * @brief HTTPRequest::isValid
 * @return
 */
bool HTTPRequest::isValid() {
    return valid;
}

/**
 * Accessor
 * @brief HTTPRequest::setValid
 * @param value
 */
void HTTPRequest::setValid(bool value) {
    valid = value;
}

/**
 * Recovers type of request
 * @brief HTTPRequest::parseType
 * @param s
 * @return string || NULL
 */
string HTTPRequest::parseType(string s) {
    if (s.size() != 0) {
        unsigned end = s.find_first_of(" ");

        string reqType;
        for (unsigned i = 0; i < end; i++) {
            reqType += s.at(i);
        }
        setValid(true);
        return reqType;
    } else {
        setValid(false);
        return "";
    }
}

/**
 * Recovers client's request
 * @brief HTTPRequest::parseRequest
 * @param s
 * @return string || NULL
 */
string HTTPRequest::parseRequest(string s) {
    if (s.size() != 0) {
        unsigned begin = s.find_first_of(" ");
        unsigned end = s.find_first_of(" ", begin+1);

        string request;
        for (unsigned i = (begin + 1); i < end; i++) {
            request +=  s.at(i);
        }
        setValid(true);
        return request;
    } else {
        setValid(false);
        return "";
    }
}

/**
 * Accessor
 * @brief HTTPRequest::getRequest
 * @return
 */
string HTTPRequest::getRequest() {
    return request;
}

/**
 * Accessor
 * @brief HTTPRequest::getType
 * @return
 */
string HTTPRequest::getType() {
    return type;
}

/**
 * Destructor
 * @brief HTTPRequest::~HTTPRequest
 */
HTTPRequest::~HTTPRequest() {
    request.erase();
    type.erase();
}







