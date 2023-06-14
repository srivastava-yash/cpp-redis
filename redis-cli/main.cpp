#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include "../utils/string_utility.h"
#define PORT 6378

int main(int argc, char const* argv[]) {

    int status, valread, client_fd;
    struct sockaddr_in serv_addr;

    // creating socket
    char buffer[1024] = { 0 };
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n redis-cli: Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf(
            "\nInvalid address/ Address not supported \n");
        return -1;
    }

    // Connecting to socket
    if ((status = connect(client_fd, (struct sockaddr*)&serv_addr,
                   sizeof(serv_addr))) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    printf("Connection established\n");

    // client commands input logic
    while(true) {
        std::cout<<">";
        std::string input;
        std::getline(std::cin, input);

        string cmd = split_string(input)[0];
        transform(cmd.begin(), cmd.end(), cmd.begin(), ::toupper);

        if(cmd == "EXIT" || cmd == "QUIT" || cmd == "Q") {
            break;
        }
        
        int sentBytes; 
        if (sentBytes = send(client_fd, input.c_str(), input.size(), 0) < 0) {
            printf("\nError while sending data to server\n");
            continue;
        }

        valread = read(client_fd, buffer, 1024);
        printf("%s\n", buffer);
    }

    return 0;

}