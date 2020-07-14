all: client server

client:
	g++ -Wall -o client client.cpp -I../src/ ../src/TCPServer.cpp ../src/TCPClient.cpp -std=c++11 -lpthread

server:
	g++ -Wall -o server server.cpp -I../src/ ../src/TCPServer.cpp ../src/TCPClient.cpp -std=c++11 -lpthread

.PHONY: clean

clean:
	@echo clean...
	@rm -rf client
	@rm -rf server