#include "httpanswer.h"

using namespace std;

HTTPAnswer::HTTPAnswer(string module, string page)  {
    cout << module << endl;
    cout << page << endl;
}

string HTTPAnswer::createAnswer(string request) {
    cout << request << endl;
    return "";
}
