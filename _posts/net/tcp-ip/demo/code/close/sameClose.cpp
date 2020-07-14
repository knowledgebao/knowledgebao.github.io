#include <chrono>
#include <csignal>
#include <iostream>
#include <thread>
#include "TCPClient.h"

using namespace chrono;

TCPClient tcp;

void sig_exit(int s) {
    tcp.exit();
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
            to_string(sec);
    return date;
}

int clientConn(string ip, int port) {
    sleep(1);
    auto ret = tcp.setup(ip, port);
    if (ret) {
        cerr << "ip:" << tcp.GetLocalIP() << " port:" << tcp.GetLocalPort() << " , connect ok " << endl;
    } else {
        cerr << "ip:" << tcp.GetLocalIP() << " port:" << tcp.GetLocalPort() << " , connect fail " << endl;
    }
    cerr << "connect out" << endl;
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: ./server port" << endl;
        return 0;
    }
    std::signal(SIGINT, sig_exit);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serverAddress;
    memset(&serverAddress, 0, sizeof(serverAddress));

    vector<int> opts = {SO_REUSEPORT, SO_REUSEADDR};
    for (unsigned int i = 0; i < opts.size(); i++) {
        int opt = 1;
        if ((setsockopt(sockfd, SOL_SOCKET, opts.size(), (char*)&opt, sizeof(opt))) < 0) {
            cerr << "Errore setsockopt" << endl;
            return -1;
        }
    }

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

    std::thread conn(clientConn, "127.0.0.1", atoi(argv[1]));

    struct sockaddr_in clientAddress;
    socklen_t sosize = sizeof(clientAddress);
    auto socket = accept(sockfd, (struct sockaddr*)&clientAddress, &sosize);
    auto ip = inet_ntoa(clientAddress.sin_addr);
    auto port = ntohs(clientAddress.sin_port);
    cerr << "accept client: " << ip << "," << port << " handle:" << socket << endl;
    conn.join();
    std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();

    std::thread([&]() {
        cerr << "client exit" << endl;
        while (1) {
            std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
            if (std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() > 1000) {
                tcp.exit();
                break;
            }
        }
    });
    std::thread([&]() {
        cerr << "server client exit" << endl;
        while (1) {
            std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
            if (std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() > 1000) {
                close(socket);
                break;
            }
        }
    });

    cerr << "server close" << endl;
    close(sockfd);

    return 0;
}
