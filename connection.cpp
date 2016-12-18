#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include "connection.h"
#include "program_util.h"

connection::connection() {}

connection::~connection() {
  close(sockfd);
}

void connection::prepare_server(int argc, char** argv) {
  if(argc != PROGRAM_ARGSIZE) throw arg_runtime_error
                                ("Expected 3 arguments, but found "
                                + std::to_string(argc));

  try {
    portno = std::stoi(argv[2]);
  } catch (std::invalid_argument& e) {
    throw arg_runtime_error("Port number is not valid");
  }

  server_hostent = gethostbyname(argv[1]);
  if(server_hostent == NULL) throw arg_runtime_error
                          ("Invalid host name");
}

void connection::prepare_connect() {
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
      throw connect_runtime_error("Failed to open socket for connection.");

  bzero((char *) &server_addr, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  bcopy((char *)server_hostent->h_addr,
       (char *)&server_addr.sin_addr.s_addr,
       server_hostent->h_length);

  server_addr.sin_port = htons(portno);
  if (connect(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0)
      throw connect_runtime_error("ERROR connecting to the created socket.");
}

void connection::build_connection(int argc, char** argv) {
  prepare_server(argc, argv);
  prepare_connect();
}

int connection::get_connection_sockfd() const {
  return sockfd;
}
