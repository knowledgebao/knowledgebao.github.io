from socketserver import BaseRequestHandler, TCPServer
import datetime

class EchoHandler(BaseRequestHandler):
    def handle(self):
        print('Got connection from', self.client_address)
        while True:
            msg = self.request.recv(8192)
            if not msg:
                break
            print("recv:",datetime.datetime.now(),len(msg),msg)
        print("over:",self.client_address)

if __name__ == '__main__':
    serv = TCPServer(('', 2362), EchoHandler)
    print("liston 2362 ok")
    serv.serve_forever()