#include <csignal>
#include <ctime>
#include <iostream>
#include<netinet/tcp.h>
#include "TCPServer.h"

TCPServer tcp;

void close_app(int s) {
    tcp.closed();
    exit(0);
}

string getTime() {
    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);
    int hour = now->tm_hour;
    int min = now->tm_min;
    int sec = now->tm_sec;

    std::string date =
            to_string(now->tm_year + 1900) + "-" +
            to_string(now->tm_mon + 1) + "-" +
            to_string(now->tm_mday) + " " +
            to_string(hour) + ":" +
            to_string(min) + ":" +
            to_string(sec) + "." +
            to_string(int(t%1000));
    return date;
}

// 应用TCP保活机制的相关代码
//keepalive_time:保活时间间隔，keepalive_intvl：保活探测包间隔，keepalive_probes：保活探测包个数
int set_keepalive(int sockfd, int keepalive_time, int keepalive_intvl, int keepalive_probes) {
    int optval;
    socklen_t optlen = sizeof(optval);
    optval = 1;
    if (-1 == setsockopt(sockfd, SOL_SOCKET, SO_KEEPALIVE, &optval, optlen)) {
        perror("setsockopt failure.");
        return -1;
    }

    optval = keepalive_probes;
    if (-1 == setsockopt(sockfd, SOL_TCP, TCP_KEEPCNT, &optval, optlen)) {
        perror("setsockopt failure.");
        return -1;
    }

    optval = keepalive_intvl;
    if (-1 == setsockopt(sockfd, SOL_TCP, TCP_KEEPINTVL, &optval, optlen)) {
        perror("setsockopt failure.");
        return -1;
    }

    optval = keepalive_time;
    if (-1 == setsockopt(sockfd, SOL_TCP, TCP_KEEPIDLE, &optval, optlen)) {
        perror("setsockopt failure.");
        return -1;
    }
    return 0;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "Usage: ./server port" << endl;
        return 0;
    }
    std::signal(SIGINT, close_app);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serverAddress;
    memset(&serverAddress, 0, sizeof(serverAddress));

    int v = 1;
    if ((setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT, (char*)&v, sizeof(int))) < 0
        || (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char*)&v, sizeof(int))) < 0) {
        cerr << "Errore setsockopt SO_REUSEPORT" << endl;
        return -1;
    }
    set_keepalive(sockfd,30,5,3);//30秒不发数据，发送探测包5秒一个，一共3次

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port = htons(atoi(argv[1]));

    if ((::bind(sockfd, (struct sockaddr*)&serverAddress, sizeof(serverAddress))) < 0) {
        cerr << "Errore bind" << endl;
        return -1;
    }

    if (listen(sockfd, 5) < 0) {
        cerr << "Errore listen" << endl;
        return -1;
    }
    cerr << getTime() << " : " << argv[1] << " is listem" << endl;

    struct sockaddr_in clientAddress;
    socklen_t sosize = sizeof(clientAddress);
    auto socket = accept(sockfd, (struct sockaddr*)&clientAddress, &sosize);
    auto ip = inet_ntoa(clientAddress.sin_addr);
    auto port = ntohs(clientAddress.sin_port);
    
    cerr << "accept client["
         << " ip:" << ip << ","
         << port << " handle:" << socket << " ]" << endl;
    while (true){
        sleep(1);
        cerr << getTime() <<endl;
    }

    return 0;
}
