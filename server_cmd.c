#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "server_cmd.h"

void *connection_handler(void *socket_desc)
{

    int sock = *(int*)socket_desc;
    int read_size;
    char buffer[BUFFER_SIZE];
    char client_buffer[BUFFER_SIZE];

    strcat(buffer, "Galaxy IRC\n");
    write(sock, buffer, strlen(buffer));

    while ((read_size = recv(sock, client_buffer, sizeof(client_buffer), 0)) > 0) {
        buffer[0] = '\0';
        strcat(buffer, "Client: ");
        strcat(buffer, client_buffer);
        send(sock, buffer, sizeof(buffer), 0);
    }

    if (read_size == 0) {
        puts("Client disconnected.");
        fflush(stdout);
    } else if (read_size == -1) {
        perror("recv failed!");
    }

    free(socket_desc);

    return 0;

}

