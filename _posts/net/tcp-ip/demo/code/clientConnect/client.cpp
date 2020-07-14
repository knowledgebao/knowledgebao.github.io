#include <signal.h>
#include <iostream>
#include <csignal>
#include <ctime>
#include <iostream>
#include "TCPClient.h"

TCPClient tcp;
void sig_exit(int s) {
    for (size_t i = 0; i < 5; i++) {
        tcp.exit();
    }
    cout<<"client sig_exit"<<endl;
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
    for (;;){
        if(tcp.Send("hello,i am client")){
            cout<<getTime()<<": send ok" << endl;
        }else{
            cout<<getTime()<<": send fail" << endl;
        }
        sleep(2);
    }

    return 0;
}
