all:
	g++ -o client client.cpp
	g++ -o server server.cpp

clean:
	rm -rf client server
