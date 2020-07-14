#include <signal.h>
#include <iostream>
#include "TCPClient.h"

TCPClient tcp;

void sig_exit(int s) {
    tcp.exit();
    exit(0);
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cerr << "Usage: ./client ip port message" << endl;
        return 0;
    }
    signal(SIGINT, sig_exit);
    auto ret = tcp.setup(argv[1], atoi(argv[2]));
    if (ret) {
        cout << "ip:" << tcp.GetLocalIP() << " port:" << tcp.GetLocalPort() << " , connect ok " << endl;
    } else {
        cout << "ip:" << tcp.GetLocalIP() << " port:" << tcp.GetLocalPort() << " , connect fail " << endl;
    }
    tcp.Send(argv[3]);
    tcp.Shutdown();
    while (1) {
        string rec = tcp.receive();
        if (rec != "") {
            cout << "S -> C: " << rec << endl;
        }
        sleep(1);
    }

    return 0;
}
