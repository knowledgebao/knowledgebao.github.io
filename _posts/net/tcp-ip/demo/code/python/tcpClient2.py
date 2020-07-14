from os import name
import socket
from socket import SHUT_WR
import time
from time import ctime
import threading

data = [1]*4096
sendData = bytes(data)

def Connect(ip,port,name):
    server_ip = ip
    servr_port = port
 
    tcp_client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
 
    try:
        tcp_client.bind(('10.156.10.62', port))
        tcp_client.connect((server_ip, servr_port))
    except socket.error:
        print('fail to setup socket connection')
    else:
        print('sending..........')
        # tcp_client.sendall(b"echo message")
 
        print('reading...........')
        # print(tcp_client.recv(10))
    tcp_client.close()

if __name__ == "__main__":
    Connect("10.156.10.150",2362,"150")    