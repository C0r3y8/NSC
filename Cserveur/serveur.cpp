#include "serveur.h"
#include <iostream>

using namespace std;


/**
 * Default constructor
 * Initilizing port to 80
 * @brief Serveur::Serveur
 */
Serveur::Serveur(): port(80), isStart(false), stopServeur(false) {}

/**
 * Consructor
 * Initiliazing port and isStart
 * @brief Serveur::Serveur
 * @param port
 */
Serveur::Serveur(int p): port(p), isStart(false), stopServeur(false) {}

/**
 * Initializing serveur's address
 * @brief Serveur::init
 * @return bool false if no error occurred
 */
int Serveur::init() {
    /*
     *Configuration for Windows
     */
    #ifdef _WIN32
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
            cerr << "WSAStartup failed" << endl;
            return 1;
        }
    #endif

    struct in_addr address;
    struct hostent *host;
    char hostname[100];

    if (gethostname(hostname, 100) == SOCKET_ERROR) {
        #ifdef _WIN32
            cerr << "Error gethostname(): " << WSAGetLastError() << endl;
        #else
            cerr << "Error gethostname()" << endl;
        #endif
        return 1;
    }

    host = gethostbyname(hostname);
    if (host == NULL) {
        #ifdef _WIN32
            cerr << "Error gethostbyname(): " << WSAGetLastError() << endl;
        #else
            cerr << "Error gethostbyname()" << endl;
        #endif
        return 1;
    }

    memcpy(&address.s_addr, host->h_addr_list[0], sizeof(address.s_addr));

    addrServeur.sin_family = AF_INET;
    addrServeur.sin_port = htons(port);
    addrServeur.sin_addr.s_addr = inet_addr(inet_ntoa(address));

    cout << "Successfully intialized" << endl;
    return 0;
}

/**
 * Start the serveur
 * @brief Serveur::start
 * @return bool false if no error occurred
 */
int Serveur::start() {
    SOCKADDR_IN addrClient;
    SOCKET sockClient;
    pthread_t thread;
    struct thread_params params;

    sockServeur = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockServeur != INVALID_SOCKET) {
         int bind_err = bind(sockServeur, (SOCKADDR *) &addrServeur, sizeof(addrServeur));
        if (bind_err == SOCKET_ERROR) {
            #ifdef _WIN32
                cerr << "Socket bind failed: " << WSAGetLastError() << endl;
                closesocket(sockServeur);
                WSACleanup();
            #else
                cerr << "Socket bind failed: "  << errno << endl;
                close(sockServeur);
            #endif
            return 1;
        }
    } else {
        #ifdef _WIN32
            cerr << "Socket creation failed: " << WSAGetLastError() << endl;
            WSACleanup();
        #else
            cerr << "Socket creation failed: "  << errno << endl;
        #endif
        return 1;
    }

    cout << "Successfully starting serveur on port: " << port;
    cout << " and IP: " << inet_ntoa(addrServeur.sin_addr) << endl << endl;

    do {

        int listen_err = listen(sockServeur, 5);
        if (listen_err == SOCKET_ERROR) {
            #ifdef _WIN32
                cerr << "Socket listen failed: " << WSAGetLastError() << endl;
                closesocket(sockServeur);
                WSACleanup();
            #else
                cerr << "Socket listen failed: " << errno << endl;
                close(sockServeur);
            #endif
            return 1;
        } else {
            setStart(true);
        }

        if (this->acceptClient(sockClient, addrClient) != false) {
            return 1;
        }

        params.serv = this;
        params.sockClient = sockClient;
        params.addrClient = addrClient;

        int thread_err = pthread_create(&thread, NULL, Manager::handling, (void*) &params);
        if (thread_err != 0) {
            cerr << "Creation of thread failed" << endl;
            #ifdef _WIN32
                closesocket(sockServeur);
                WSACleanup();
            #else
                close(sockServeur);
            #endif
            return 1;
        }

    } while(stopServeur == false);
    return 0;
}

/**
 * Stop the serveur
 * @brief Serveur::stop
 * @return bool false if no error occurred
 */
int Serveur::stop() {
    #ifdef _WIN32
        closesocket(sockServeur);
    #else
        close(sockServeur);
    #endif
    setStart(false);
    cout << "Serveur stopped" << endl;
    return 0;
}

/**
 * Return the status of the serveur
 * @brief Serveur::isStarted
 * @return bool
 */
bool Serveur::isStarted() {
    return isStart;
}

int Serveur::acceptClient(SOCKET &sockClient, SOCKADDR_IN &addrClient) {
    int addrClientLen = sizeof(addrClient);
    #ifdef _WIN32
        sockClient = accept(sockServeur, (SOCKADDR *) &addrClient, &addrClientLen);
    #else
        sockClient = accept(sockServeur, (SOCKADDR *) &addrClient, (socklen_t*)&addrClientLen);
    #endif
    if (sockClient == INVALID_SOCKET) {
        #ifdef _WIN32
            cerr << "Socket accept failed: " << WSAGetLastError() << endl;
            closesocket(sockServeur);
            WSACleanup();
        #else
            cerr << "Socket accept failed: " << errno << endl;
            close(sockServeur);
        #endif
        return 1;
    }
    return 0;
}


/**
 * Recive the request of the client
 * @brief Serveur::reciveRequest
 * @return
 */
string Serveur::reciveRequest(SOCKET sockClient, SOCKADDR_IN addrClient) {
    char buffer[BUFFERSIZE];
    string request;
    int addrClientLen = sizeof(addrClient);

    #ifdef _WIN32
        int recv_err = recvfrom(sockClient, (char*) &buffer, BUFFERSIZE, 0, (SOCKADDR *) &addrClient, &addrClientLen);
    #else
        int recv_err = recvfrom(sockClient, (char*) &buffer, BUFFERSIZE, 0, (SOCKADDR *) &addrClient, (socklen_t*)&addrClientLen);
    #endif

    if (recv_err == SOCKET_ERROR) {
        #ifdef _WIN32
            cerr << "Socket recv failed: " << WSAGetLastError() << endl;
            closesocket(sockServeur);
            WSACleanup();
        #else
            cerr << "Socket recv failed: " << errno << endl;
            close(sockServeur);
        #endif
            return (char*) "failed";
    }
    request = string(buffer);
    return request;
}

void Serveur::setStart(bool start) {
    isStart = start;
}


/**
 * Accessor
 * @brief Serveur::setStopServeur
 * @param stop
 */
void Serveur::setStopServeur(bool stop) {
    stopServeur = stop;
    if (stop == true) {
        setStart(false);
    }
}

/**
 * Accessor
 * @brief Serveur::getStopServeur
 * @return stopServeur
 */
bool Serveur::getStopServeur() {
    return stopServeur;
}


/**
 * Destructor
 * @brief Serveur::~Serveur
 */
Serveur::~Serveur() {}
