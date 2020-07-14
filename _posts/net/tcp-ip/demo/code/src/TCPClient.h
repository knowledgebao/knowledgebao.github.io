#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <vector>

using namespace std;

class TCPClient {
private:
    int sock;
    struct sockaddr_in server;
    struct sockaddr_in client;

public:
    TCPClient();
    bool setup(string address, int port, string localIP = "", int localPort = 0);
    bool Send(string data);
    string receive(int size = 4096);
    string read();
    void exit();
    string GetLocalIP();
    int GetLocalPort();
    string GetRemoteIP();
    int GetRemotePort();
    int Shutdown(int how = SHUT_WR);
};

#endif
