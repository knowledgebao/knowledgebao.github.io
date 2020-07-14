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
    if (argc != 4) {
        cerr << "Usage: ./client ip port type(1:sleep,2:restart,3,close)" << endl;
        return 0;
    }
    signal(SIGINT, sig_exit);
    auto ret = tcp.setup(argv[1], atoi(argv[2]));
    if (ret) {
        cout << ": ip:" << tcp.GetLocalIP() << " port:" << tcp.GetLocalPort() << " , connect ok " << endl;
    } else {
        cout << ": ip:" << tcp.GetLocalIP() << " port:" << tcp.GetLocalPort() << " , connect fail " << endl;
    }
    if (string(argv[3]) == "1"){
        while (true){
            sleep(1);
        }
    }else if (string(argv[3]) == "2"){
        auto ret = tcp.setup(argv[1], atoi(argv[2]));
        if (ret) {
            cout << ": ip:" << tcp.GetLocalIP() << " port:" << tcp.GetLocalPort() << " , connect ok " << endl;
        } else {
            cout << ": ip:" << tcp.GetLocalIP() << " port:" << tcp.GetLocalPort() << " , connect fail " << endl;
        }
        while (true){
            sleep(1);
        }  
    }
    
    
    sleep(1);
    return 0;
}
