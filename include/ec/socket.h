
#pragma once

#if defined(__WIN32) || defined(__linux__)

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#if defined(__WIN32)

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0600
#endif
#include <winsock2.h>
#include <ws2tcpip.h>

#elif defined(__linux__)

#include <arpa/inet.h>
#include <sys/wait.h>
#include <sys/time.h>

#endif

#if defined(__linux__)
#define socket_t int
#elif defined(__WIN32)
#define socket_t SOCKET
#endif

int64_t ipLookup(const char *hostname);
struct sockaddr_in socket_generate(const char *hostname, uint16_t port);
void socket_close(socket_t socketDescriptor);

typedef struct
{
    socket_t socket_descriptor;
    bool     connected;
} TCP_Client;

TCP_Client tcp_client_connect     (const char *hostname, uint16_t port);
void       tcp_client_disconnect  (TCP_Client *client);
void       tcp_client_send        (TCP_Client *client, const char *msg);
size_t     tcp_client_receive_sync(TCP_Client *client, char *ptr, size_t ptrlen);
size_t     tcp_client_receive     (TCP_Client *client, char *ptr, size_t ptrlen,
                                      int timeout_sec, int timeout_usec);

#ifdef __cplusplus
}
#endif


#endif
