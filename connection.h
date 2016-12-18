#ifndef __SERVER_CONFIG__
#define __SERVER_CONFIG__

#include <netdb.h>

typedef struct hostent hostent;
typedef struct sockaddr_in sockaddr_in;
class connection {
  private:
    hostent* server_hostent;
    sockaddr_in server_addr;
    int portno;
    int sockfd;
    void prepare_server(int argc, char** argv);
    void prepare_connect();
  public:
    connection();
    ~connection();

    void build_connection(int argc, char** argv);
    int get_connection_sockfd() const;
};

#endif
