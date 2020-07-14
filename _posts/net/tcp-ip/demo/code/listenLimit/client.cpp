#include <signal.h>
#include <iostream>
#include "TCPClient.h"

TCPClient tcp[5];
void sig_exit(int s) {
    for (size_t i = 0; i < 5; i++) {
        tcp[i].exit();
    }
    exit(0);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: ./client ip port" << endl;
        return 0;
    }
    signal(SIGINT, sig_exit);
    for (size_t i = 0; i < 10; i++) {
        auto ret = tcp[i].setup(argv[1], atoi(argv[2]));
        if (ret) {
            cout << i << ": ip:" << tcp[i].GetLocalIP() << " port:" << tcp[i].GetLocalPort() << " , connect ok " << endl;
        } else {
            cout << i << ": ip:" << tcp[i].GetLocalIP() << " port:" << tcp[i].GetLocalPort() << " , connect fail " << endl;
        }
    }
    while (true) {
        sleep(1);
    }

    return 0;
}
