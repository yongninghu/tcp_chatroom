COMPILECPP = g++ -g -O0 -Wall -Wextra -Wfatal-errors -std=c++11

CLIENTCPPSOURCE = client.cpp program_util.cpp connection.cpp chatroom.cpp
CLIENTOBJECTS	= ${CLIENTCPPSOURCE:.cpp=.o}
CLIENTEXECBIN	= client

SERVERCPPSOURCE = server.cpp
SERVEROBJECTS = ${SERVERCPPSOURCE:.cpp=.o}
SERVEREXECBIN = server

all : ${CLIENTEXECBIN} ${SERVEREXECBIN}

${CLIENTEXECBIN} : ${CLIENTOBJECTS}
	${COMPILECPP} -o $@ ${CLIENTOBJECTS}

${SERVEREXECBIN} : ${SERVEROBJECTS}
	${COMPILECPP} -o $@ ${SERVEROBJECTS}

%.o : %.cpp
	${COMPILECPP} -c $<

clean :
	rm *.o server client
	
