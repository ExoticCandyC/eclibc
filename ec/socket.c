
#if defined(__WIN32) || defined(__linux__)

#include <ec/socket.h>

#include <fcntl.h>
#include <unistd.h>

#include <ec/io.h>
#include <ec/string.h>

#if defined(__WIN32)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#pragma GCC diagnostic ignored "-Wsign-conversion"
#endif

#if defined(__WIN32)

int64_t ipLookup(const char *hostname)
{
    WSADATA d;
    WSAStartup(MAKEWORD(2, 2), &d);
    struct hostent* host = gethostbyname(hostname);
    return inet_addr(inet_ntoa(*(struct in_addr*)*host->h_addr_list));
}

#elif defined(__linux__)

int64_t ipLookup(const char *hostname)
{
    char response[1024];
    char command[1024];
    char *ptr = response;
    char *ptr2;
    int64_t addr;
    ec_sprintf(command, "ping -c 1 -t 1 %s", hostname);
    ec_popen(command, response, sizeof(response));
    while(*ptr != '(' && *ptr != '\0')
        ptr++;
    if(*ptr == '\0')
        return -1;
    ptr++;
    ptr2 = ptr;
    while(*ptr2 != ')' && *ptr2 != '\0')
        ptr2++;
    if(*ptr2 == '\0')
        return -1;
    *ptr2 = '\0';
    addr = inet_addr(ptr);
    return addr;
}

#endif

struct sockaddr_in socket_generate(const char *hostname, uint16_t port)
{
    struct sockaddr_in sendSockAddr;
    memset((void*)&sendSockAddr, 0, sizeof(sendSockAddr));
    sendSockAddr.sin_family = AF_INET;
    #if defined(__linux__)
    sendSockAddr.sin_addr.s_addr = (in_addr_t)ipLookup(hostname);
    #elif defined(__WIN32)
    sendSockAddr.sin_addr.s_addr = (u_long)ipLookup(hostname);
    #endif
    sendSockAddr.sin_port = htons(port);
    return sendSockAddr;
}

TCP_Client tcp_client_connect(const char *hostname, uint16_t port)
{
    TCP_Client client;
    struct sockaddr_in sockaddress = socket_generate(hostname, port);

    client.socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    client.connected = (connect(client.socket_descriptor,
                              (struct  sockaddr*) &sockaddress,
                                sizeof(struct sockaddr)) >= 0);

    return client;
}

void tcp_client_disconnect(TCP_Client *client)
{
    socket_close(client->socket_descriptor);
}

void tcp_client_send(TCP_Client *client, const char *msg)
{
    send(client->socket_descriptor, msg, strlen(msg), 0);
}

size_t tcp_client_receive_sync(TCP_Client *client, char *ptr, size_t ptrlen)
{
    size_t bytesIn = (size_t)recv(client->socket_descriptor, ptr, ptrlen, 0);
    if(bytesIn < 1)
        client->connected = false;
    return bytesIn;
}

size_t tcp_client_receive(TCP_Client *client, char *ptr, size_t ptrlen,
                                             int timeout_sec, int timeout_usec)
{
    size_t bytesIn = 0;

    fd_set reads;
    FD_ZERO(&reads);
    FD_SET( client->socket_descriptor, &reads);
    #if defined(__linux__)
    FD_SET(0, &reads);
    #endif
    struct timeval timeout;
    timeout.tv_sec  = timeout_sec;
    timeout.tv_usec = timeout_usec;

    /* select failed */
    if (select((int)(client->socket_descriptor + 1), &reads, 0, 0, &timeout) < 0)
        return bytesIn;

    if (FD_ISSET( client->socket_descriptor , &reads))
    {
        bytesIn = (size_t)recv(client->socket_descriptor, ptr, ptrlen, 0);
        if(bytesIn < 1)
            client->connected = false;
    }

    return bytesIn;
}

void socket_close(socket_t socketDescriptor)
{
    #if defined(__WIN32)
    closesocket(socketDescriptor);
    #elif defined(__linux__)
    close(socketDescriptor);
    #endif
}

#if defined(__WIN32)
#pragma GCC diagnostic pop
#endif

#else

typedef int A_TYPEDEF_TO_AVOID_PEDANTIC_WARNINGS;

#endif
