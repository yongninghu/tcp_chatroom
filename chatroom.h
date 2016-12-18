#ifndef __CHATROOM__
#define __CHATROOM__

class chatroom {
  private:
    static int sockfd;
    static void write_to_socket();
    static void read_from_socket();
  public:
    chatroom();
    ~chatroom();
    void start_chatting(int input_sockfd);
};

#endif
