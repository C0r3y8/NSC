#include "httpquery.h"

using namespace std;

/**
 * Constructor
 * @brief HTTPQuery::HTTPQuery
 * @param c
 */
HTTPQuery::HTTPQuery(string s) {
    string query;

    type = Parser::parseType(s);
    query = Parser::parseQuery(s);

    module = Parser::parseModule(&query);
    page = Parser::parsePage(&query);
    params = Parser::parseParams(s);
}


/**
 * Accessor
 * @brief HTTPQuery::getType
 * @return string (type)
 */
string HTTPQuery::getType() {
    return type;
}

/**
 * Accessor
 * @brief HTTPQuery::getModule
 * @return string (module)
 */
string HTTPQuery::getModule() {
    return module;
}

/**
 * Accessor
 * @brief HTTPQuery::getPage
 * @return string (page)
 */
string HTTPQuery::getPage() {
    return page;
}

/**
 * Accessor
 * @brief HTTPQuery::getParams
 * @return map<string, string> (params)
 */
map<string, string> HTTPQuery::getParams() {
    return params;
}

/**
 * Destructor
 * @brief HTTPQuery::~HTTPQuery
 */
HTTPQuery::~HTTPQuery() {
    module.erase(module.begin(), module.end());
    page.erase(page.begin(), page.end());
    params.erase(params.begin(), params.end());
    type.erase(type.begin(), page.end());
}







