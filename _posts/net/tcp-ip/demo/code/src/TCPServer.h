#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <algorithm>
#include <cctype>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

using namespace std;

#define MAXPACKETSIZE 40960
#define MAX_CLIENT 1000
//#define CODA_MSG 4

struct descript_socket {
    int socket = -1;
    string ip = "";
    int port = -1;
    int id = -1;
    std::string message;
    bool enable_message_runtime = false;
};

class TCPServer {
public:
    int setup(int port, vector<int> opts = vector<int>(), int limit = 5);
    vector<descript_socket*> getMessage();
    void accepted();
    void Send(string msg, int id);
    void detach(int id);
    void clean(int id);
    bool is_online();
    string get_ip_addr(int id);
    int get_last_closed_sockets();
    void closed();

private:
    int sockfd, n, pid;
    struct sockaddr_in serverAddress;
    struct sockaddr_in clientAddress;
    pthread_t serverThread[MAX_CLIENT];

    static vector<descript_socket*> newsockfd;
    static char msg[MAXPACKETSIZE];
    static vector<descript_socket*> Message;  //[CODA_MSG];

    static bool isonline;
    static int last_closed;
    static int num_client;
    static std::mutex mt;
    static void* Task(void* argv);
};

#endif
