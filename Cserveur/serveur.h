#ifndef SERVEUR_H
#define SERVEUR_H
#define BUFFERSIZE 5000

#ifdef _WIN32
    #include <winsock2.h>
#elif defined (linux)
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>

    #include <string.h> // memcpy under linux

    #include <unistd.h> /* close */
    #include <netdb.h> /* gethostbyname */
    #include <stdio.h>
    #include <stdlib.h>
    #include <errno.h>

    #define INVALID_SOCKET -1
    #define SOCKET_ERROR -1
    #define closesocket(s) close(s)

    typedef int SOCKET;
    typedef struct sockaddr_in SOCKADDR_IN;
    typedef struct sockaddr SOCKADDR;
    typedef struct in_addr IN_ADDR;

#else /* For other platforms, like GameBoy Advance or n64 */
    #error invalid platform !
#endif

#include <iostream>
#include <pthread.h>
#include "manager.h"

/**
 * Class Serveur
 * Initialize and start a serveur
 * Default port is 80
 * Protocole is TCP
 *
 * @author Stéphane Barale <stephane.barale@gmail.com>
 * @brief The Serveur class
 * @since v0.1
 */
class Serveur {
    public:
        Serveur();
        Serveur(int);
        int init();
        int start();
        int stop();
        std::string reciveRequest(SOCKET, SOCKADDR_IN);
        int acceptClient(SOCKET&, SOCKADDR_IN&);

        void setStopServeur(bool);
        bool getStopServeur();

        bool isStarted();
        void setStart(bool);
        virtual ~Serveur();

    private:
        bool stopServeur;
        int port;
        SOCKET sockServeur;
        bool isStart;
        SOCKADDR_IN addrServeur;
};

struct thread_params{
    Serveur *serv;
    SOCKET sockClient;
    SOCKADDR_IN addrClient;
};
#endif // SERVEUR_H
