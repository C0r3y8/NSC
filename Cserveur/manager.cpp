#include "manager.h"
#include <iostream>

using namespace std;

/**
 * Handling for request of the client
 * @brief Manager::handling
 * @param params
 * @return
 */
void* Manager::handling(void *params) {
    struct thread_params *Obj = reinterpret_cast<struct thread_params*>(params);
    Serveur *serveur = Obj->serv;
    SOCKET sockClient = Obj->sockClient;
    SOCKADDR_IN addrClient = Obj->addrClient;

    string request = serveur->reciveRequest(sockClient, addrClient);

    HTTPRequest* http = new HTTPRequest(request);
    cout << "Request of the client" << endl;
    cout << "---------------------------------" << endl;
    cout << http->getRequest() << endl;
    cout << "---------------------------------" << endl;
    cout << http->getType() << endl;
    cout << "End of request" << endl;

    delete http;

    return (void*)0;
}
