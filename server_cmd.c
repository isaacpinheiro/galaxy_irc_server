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
    send(sock, buffer, sizeof(buffer), 0);

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

void insert_user(User *list, char *name)
{
    if (list->next != NULL) {
        insert_user(list->next, name);
    } else {
        User *new = (User*) malloc(sizeof(User));
        new->next = NULL;
        list->name[0] = '\0';
        strcat(list->name, name);
        list->next = new;
    }
}

User *remove_user(User *list, char *name)
{
    return NULL;
}

void show_users(User *list, char *buffer)
{
    if (list->next != NULL) {
        strcat(buffer, list->name);
        strcat(buffer, "\n");
        show_users(list->next, buffer);
    }
}

