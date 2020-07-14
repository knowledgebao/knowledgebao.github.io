#include "TCPClient.h"

TCPClient::TCPClient() {
    sock = -1;
}

bool TCPClient::setup(string remoteIP, int remotePort, string localIP, int localPort) {
    if (sock == -1) {
        sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock == -1) {
            cout << "Could not create socket" << endl;
        }
    }
    if (!localIP.empty()) {
        bzero(&client, sizeof(client));
        client.sin_family = AF_INET;
        client.sin_port = htons(localPort);
        inet_pton(AF_INET, localIP.c_str(), &client.sin_addr);
        if (bind(sock, (struct sockaddr*)&client, sizeof(client)) == -1) {
            cout << "Failed to bind " << localPort << "," << localIP << endl;
            return false;
        }
    }

    if ((signed)inet_addr(remoteIP.c_str()) == -1) {
        struct hostent* he;
        struct in_addr** addr_list;
        if ((he = gethostbyname(remoteIP.c_str())) == NULL) {
            herror("gethostbyname");
            cout << "Failed to resolve hostname\n";
            return false;
        }
        addr_list = (struct in_addr**)he->h_addr_list;
        for (int i = 0; addr_list[i] != NULL; i++) {
            server.sin_addr = *addr_list[i];
            break;
        }
    } else {
        server.sin_addr.s_addr = inet_addr(remoteIP.c_str());
    }
    server.sin_family = AF_INET;
    server.sin_port = htons(remotePort);
    if (connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0) {
        socklen_t sosize = sizeof(client);
        getsockname(sock, (struct sockaddr*)&client, &sosize);
        perror("connect failed. Error");
        return false;
    }
    socklen_t sosize = sizeof(client);
    getsockname(sock, (struct sockaddr*)&client, &sosize);
    return true;
}

bool TCPClient::Send(string data) {
    if (sock != -1) {
        if (send(sock, data.c_str(), strlen(data.c_str()), 0) < 0) {
            cout << "Send failed : " << data << endl;
            return false;
        }
    } else
        return false;
    return true;
}

string TCPClient::receive(int size) {
    char buffer[size];
    memset(&buffer[0], 0, sizeof(buffer));

    string reply;
    if (recv(sock, buffer, size, 0) < 0) {
        cout << "receive failed!" << endl;
        return nullptr;
    }
    buffer[size - 1] = '\0';
    reply = buffer;
    return reply;
}

string TCPClient::read() {
    char buffer[1] = {};
    string reply;
    while (buffer[0] != '\n') {
        if (recv(sock, buffer, sizeof(buffer), 0) < 0) {
            cout << "receive failed!" << endl;
            return nullptr;
        }
        reply += buffer[0];
    }
    return reply;
}

void TCPClient::exit() {
    close(sock);
}

int TCPClient::Shutdown(int how) {
    return shutdown(sock, how);
}

string TCPClient::GetLocalIP() {
    return inet_ntoa(client.sin_addr);
}
int TCPClient::GetLocalPort() {
    return ntohs(client.sin_port);
}
string TCPClient::GetRemoteIP() {
    return inet_ntoa(server.sin_addr);
}
int TCPClient::GetRemotePort() {
    return ntohs(server.sin_port);
}