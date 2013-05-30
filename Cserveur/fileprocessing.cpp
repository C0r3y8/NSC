#include "fileprocessing.h"

using namespace std;

/**
 * Test if is file
 * @brief FileProcessing::is_file
 * @param name
 * @param module
 * @return bool
 */
bool FileProcessing::is_file(string name, string module = "default") {
    unsigned found;
    FILE* pFile;
    string path;

    if (module != "default" && module != "") {
        path = module + "/";
    }

    found = name.find(".html");

    if (found == string::npos) {
        path += name + ".html";
    } else {
        path += name;
    }

    pFile = fopen(path, "rb");
    if (pFile != NULL) {
        fclose(pFile);
        return true;
    }

    return false;
}


int FileProcessing::is_dir(string name) {
    unsigned found;
    DIR* pDir;

    found = name.find(".");

    if (found != string::npos) {
        return 2;
    }
    pDir = opendir(name);
    if(pDir != NULL) {
        closedir(pDir);
        return 1;
    }

    return 0;
}
