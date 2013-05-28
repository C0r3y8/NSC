#ifndef MANAGER_H
#define MANAGER_H

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

#include <pthread.h>
#include "serveur.h"
#include "httprequest.h"

/**
 * Thread execution
 *
 * @author Stéphane Barale <stephane.barale@gmail.com>
 * @brief The Manager class
 * @since v0.2
 */
class Manager {
public:
    static void* handling(void*);
};

#endif // MANAGER_H
