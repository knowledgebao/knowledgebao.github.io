from os import name
import socket
from socket import SHUT_WR
import time
from time import ctime
import threading

data = [1]*4096
sendData = bytes(data)

def Connect(ip,port,name):
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.settimeout(2)
    err_pos = 0
    try:
        s.connect((ip,port))
        print('{}({})-{} connect OK.'.format(name,err_pos,s.getsockname()))
        err_pos = 1
        # s.send(b"hello world")
        s.send(sendData)
        print('{}({})-{} send OK.'.format(name,err_pos,s.getsockname()))
        err_pos = 2
        while True:
            r = s.recv(1024)
            print('{}({})-{} recv OK.{}'.format(name,err_pos,s.getsockname(),r))
            if len(r) < 0:
                time.sleep(1)
                break
        err_pos = 3
    except Exception as e:
        print('{}({})-{} err.{}'.format(name,err_pos,s.getsockname(),e))

class myThread (threading.Thread):
    def __init__(self, name):
        threading.Thread.__init__(self)
        self.name = name
    def run(self):
        Connect("10.156.10.150",9999,self.name)

if __name__ == "__main__":
    try:
        threads = []
        for i in range(1):
            threads.append(myThread(str(i)))
        for t in threads:
            t.start()
        for t in threads:
            t.join()
        print ("退出主线程")
    except Exception as e:
        print(e)
    