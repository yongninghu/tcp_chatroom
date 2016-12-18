#include <thread>
#include <unistd.h>
#include <iostream>

#include "program_util.h"
#include "chatroom.h"

int chatroom::sockfd = UNDEFINEDFD;

chatroom::chatroom() {}

chatroom::~chatroom() {}

void chatroom::write_to_socket() {
  char buffer[256];
  while (true) {
    /* code */
    bzero(buffer,256);
    fgets(buffer,255,stdin);
    int n = write(sockfd, buffer, strlen(buffer));
    if (n < 0)
         throw chat_runtime_error("ERROR writing to socket");
  }
}

void chatroom::read_from_socket() {
  char buffer[256];
  while(true) {
    bzero(buffer,256);
    int n = read(sockfd, buffer, 255);
    if (n < 0)
        throw chat_runtime_error("ERROR reading from socket");
    std::cout << buffer;
  }
}

void chatroom::start_chatting(int input_sockfd) {
  sockfd = input_sockfd;
  std::thread write_thread(write_to_socket);
  read_from_socket();
}
