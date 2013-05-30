#ifndef HTTPANSWER_H
#define HTTPANSWER_H

#include <string.h>
#include <stdio.h>
#include <iostream>

/**
 * Create an answer for the client
 *
 * @author Stéphane Barale <stephane.barale@gmail.com>
 * @brief The HTTPAnswer class
 * @since V0.1
 */
class HTTPAnswer {
    public:
        HTTPAnswer(std::string, std::string);
        std::string getAnswer();
        std::string createAnswer(std::string);
    private:
        std::string answer;
};

#endif // HTTPANSWER_H
