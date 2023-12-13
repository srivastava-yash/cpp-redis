#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include "../utils/string_utility.h"
#include "./store.h"
#include "handle_connection.h"
using namespace std;
#define PORT 6378
#define FDMAX 1024


void make_socket_non_blocking(int sockfd) {
  int flags = fcntl(sockfd, F_GETFL, 0);
  if (flags == -1) {
    perror("fcntl F_GETFL");
  }

  if (fcntl(sockfd, F_SETFL, flags | O_NONBLOCK) == -1) {
    perror("fcntl F_SETFL O_NONBLOCK");
  }
}


int main(int argc, char const* argv[]) {

    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = { 0 };

    // Creating socket file descriptor
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    // The select() manpage warns that select() can return a read notification for
    // a socket that isn't actually readable. Thus using blocking I/O isn't safe
    make_socket_non_blocking(server_fd);
  
    // Forcefully attaching socket to the port 6378
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("attaching socket to port failed");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // bind socket to port
    int bindStatus = ::bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    if (bindStatus < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // listen for connections on the port
    int listenStatus = listen(server_fd, 5);
    if (listenStatus < 0) {
        perror("error while listenning for connections");
        exit(EXIT_FAILURE);
    }

    cout<<"Server started on port:"<<" "<<PORT<<endl;

    // Create a set of file descriptors to monitor.
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(server_fd, &readfds);
    //int fdset_max = server_fd;

    Store* store = init_store();

    while(true) {
        // select() modifies the fd_sets passed to it, so we have to pass in copies.
        fd_set currentfds = readfds;

        // Call select() to wait for activity on any of the monitored file descriptors.
        int nready = select(FDMAX, &currentfds, NULL, NULL, NULL);
        if (nready < 0) {
        perror("error in select socket");
        }
        for(int i=0;i<FDMAX;i++) {   // need to optimise this loop
            if (FD_ISSET(i, &currentfds)) {
                int new_socket;
                // case: new connection
                if(i == server_fd) {
                    new_socket = accept(i, (struct sockaddr*)&address, (socklen_t*)&addrlen);
                    if(new_socket < 0) {
                        perror("error in acceptng connection");
                        exit(EXIT_FAILURE);
                    }
                    make_socket_non_blocking(new_socket);
                    FD_SET(new_socket, &readfds);
                } else {
                    new_socket = i;
                }
                
                valread = read(new_socket, buffer, 1024);
                printf("\n%s\n", buffer);
                auto response = handle_connection(buffer, store);
                
                send(new_socket, response.first.c_str(), strlen(response.first.c_str()), 0);
                //FD_CLR(new_socket, &readfds);
            }
        }
        
    }

    cout<<"server shutdown";
    shutdown(server_fd, SHUT_RDWR);
    return 0;

}