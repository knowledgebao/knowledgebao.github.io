#include <signal.h>
#include <iostream>
#include "TCPClient.h"

TCPClient tcp;
void sig_exit(int s) {
    for (size_t i = 0; i < 5; i++) {
        tcp.exit();
    }
    exit(0);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: ./client ip port" << endl;
        return 0;
    }
    signal(SIGINT, sig_exit);
    auto ret = tcp.setup(argv[1], atoi(argv[2]));
    if (ret) {
        cout << ": ip:" << tcp.GetLocalIP() << " port:" << tcp.GetLocalPort() << " , connect ok " << endl;
    } else {
        cout << ": ip:" << tcp.GetLocalIP() << " port:" << tcp.GetLocalPort() << " , connect fail " << endl;
    }
    sleep(1);
    string data(1024,'a');
    for (size_t i = 0; i < 6; i++){
        tcp.Send(data);
    }

    return 0;
}
