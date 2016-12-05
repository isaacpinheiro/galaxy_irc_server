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

    if (list->len == 0) list->name = (char**) malloc(sizeof(char*));
    else list->name = (char**) realloc(list->name, (list->len + 1) * sizeof(char*));

    list->name[list->len] = (char*) malloc(sizeof(char) * 512);
    list->name[list->len][0] = '\0';
    strcat(list->name[list->len], name);
    list->len++;

}

char **remove_user(User *list, char *name)
{

    if (list->len == 0) return NULL;

    char **new = (char**) malloc(sizeof(char*) * (list->len-1));
    char conf = 0;
    int i, j;
    j = 0;

    for (i=0; i<list->len; i++) {
        if (strcmp(list->name[i], name) != 0) {
            new[j] = (char*) malloc(sizeof(char) * 512);
            new[j][0] = '\0';
            strcat(new[j], list->name[i]);
            j++;
        } else {
            conf = 1;
        }
    }

    if (conf) list->len--;
    free(list->name);

    return new;

}

void show_users(User *list, char *buffer)
{

    int i;

    for (i=0; i<list->len; i++) {
        strcat(buffer, list->name[i]);
        strcat(buffer, "\n");
    }

}

