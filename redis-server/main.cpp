#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
//#include "../utils/string_utility.h"
using namespace std;
#define PORT 6378


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

    while(true) {
        new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
        if(new_socket < 0) {
        perror("error in acceptng connection");
        exit(EXIT_FAILURE);
        }

        valread = read(new_socket, buffer, 1024);
        printf("\n%s\n", buffer);
        
        send(new_socket, "received", strlen("received"), 0);
    }

    cout<<"shutdown";
    shutdown(server_fd, SHUT_RDWR);
    return 0;

}