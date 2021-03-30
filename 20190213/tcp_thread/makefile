all:server client

server:
	g++ tcp_server.cc -o server -lpthread
client:
	g++ tcp_client.cc -o client
clean:
	rm -rf server client
