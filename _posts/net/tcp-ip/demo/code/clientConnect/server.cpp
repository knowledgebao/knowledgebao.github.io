#include <csignal>
#include <ctime>
#include <iostream>
#include "TCPServer.h"

TCPServer tcp;

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

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "Usage: ./server port" << endl;
        return 0;
    }
    // std::signal(SIGINT, close_app);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serverAddress;
    memset(&serverAddress, 0, sizeof(serverAddress));

    int v = 1;
    if ((setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT, (char*)&v, sizeof(int))) < 0
        || (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char*)&v, sizeof(int))) < 0) {
        cerr << "Errore setsockopt SO_REUSEPORT" << endl;
        return -1;
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port = htons(atoi(argv[1]));

    if ((::bind(sockfd, (struct sockaddr*)&serverAddress, sizeof(serverAddress))) < 0) {
        cerr << "Errore bind" << endl;
        return -1;
    }
    int recBuf = 4096;
    if ((setsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, (char*)&recBuf, sizeof(int))) < 0) {
        cerr << "Errore setsockopt SO_RCVBUF" << endl;
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
    sleep(4);
    while (true){
        char msg[512];
        auto n = recv(socket, msg, 500, 0);
        if (n != -1) {
            if (n == 0) {
                cerr << "close client["
                    << " ip : " << ip << ", " << port
                    << " socket:" << socket << " ]" << endl;
                close(socket);
            } else {
                msg[n] = 0;
                cout << getTime() << " recv: "<< msg << endl;
            }
        }
    }

    return 0;
}
