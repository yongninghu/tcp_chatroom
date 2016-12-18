#include <iostream>
#include <netdb.h>
#include <stdexcept>

#include "connection.h"
#include "program_util.h"
#include "chatroom.h"

int main(int argc, char** argv) {
  connection server_connection;
  chatroom client_chatroom;
  try {
    server_connection.build_connection(argc, argv);
    int sockfd = server_connection.get_connection_sockfd();
    client_chatroom.start_chatting(sockfd);
  } catch(std::exception& e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
