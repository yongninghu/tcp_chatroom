#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <thread>

int new_socketfd;

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

void listen_to_socket() {
  while(true) {
    char buffer[255];
    bzero(buffer,256);
    int n = read(new_socketfd,buffer,255);
    if (n < 0) error("ERROR reading from socket");
    printf("%s",buffer);
  }
}

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno;
     socklen_t clilen;
     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }

     sockfd =  socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0)
        error("ERROR opening socket");

     bzero((char *) &serv_addr, sizeof(serv_addr));

     portno = atoi(argv[1]);

     serv_addr.sin_family = AF_INET;

     serv_addr.sin_addr.s_addr = inet_addr("192.168.1.18");

     printf("%d\n",serv_addr.sin_addr.s_addr);
     serv_addr.sin_port = htons(portno);

     if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
          error("ERROR on binding");

     listen(sockfd,5);

     clilen = sizeof(cli_addr);

     newsockfd = accept(sockfd,
                 (struct sockaddr *) &cli_addr, &clilen);
     if (newsockfd < 0)
          error("ERROR on accept");

     printf("server: got connection from %s port %d\n",
            inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));

     new_socketfd = newsockfd;
     std::thread listen_thread(listen_to_socket);
     while(true) {
       bzero(buffer,256);
       fgets(buffer,255,stdin);
       n = write(newsockfd, buffer, strlen(buffer));
       if (n < 0)
            error("ERROR writing to socket");
     }

     close(newsockfd);
     close(sockfd);
     return 0;
}
