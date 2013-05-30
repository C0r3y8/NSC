#ifndef FILEPROCESSING_H
#define FILEPROCESSING_H

#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <dirent.h>

/**
 * File processing
 * @author Stéphane Barale <stephane.barale@gmail.com>
 * @brief The FileProcessing class
 * @since v0.2
 */
class FileProcessing {
public:
    FileProcessing() {}
    static bool is_file(std::string, std::string);
    static int is_dir(std::string);
};

#endif // FILEPROCESSING_H
