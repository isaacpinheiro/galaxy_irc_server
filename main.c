#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

#include "server_cmd.h"

#define MAX_PENDING 5
#define BUFFER_SIZE 1024

int main(int argc, char **argv)
{

    int server_sock;
    int client_sock;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    unsigned int client_len;
    unsigned short server_port = 9000;
    char server_ip[16];
    char buffer[BUFFER_SIZE];
    strcat(server_ip, argv[1]);

    if ((server_sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        perror("socket() failed!");
        exit(-1);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(server_port);

    if (bind(server_sock, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        perror("bind() failed!");
        exit(-1);
    }

    if (listen(server_sock, MAX_PENDING) < 0) {
        perror("listen() failed!");
        exit(-1);
    }

    client_len = sizeof(client_addr);

    if ((client_sock = accept(server_sock, (struct sockaddr *) &client_addr, &client_len)) < 0) {
        perror("accept() failed!");
        exit(-1);
    }

    while (1) {

        recv(client_sock, buffer, sizeof(buffer), 0);
        printf("%s\n\n", buffer);

        //buffer[0] = '\0';
        //strcat(buffer, "response");
        //send(client_sock, buffer, sizeof(buffer), 0);

    }

    close(client_sock);
    close(server_sock);

    return 0;

}

