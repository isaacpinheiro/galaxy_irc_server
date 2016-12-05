#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "server_cmd.h"

void *connection_handler(void *args)
{

    ThreadArgs *data = (ThreadArgs*) args;
    int sock = data->sock;
    int read_size;
    char buffer[BUFFER_SIZE];
    char client_buffer[BUFFER_SIZE];
    Message *me = (Message*) malloc(sizeof(Message));

    me->user_name[0] = '\0';
    me->command[0] = '\0';
    me->content[0] = '\0';

    while ((read_size = recv(sock, client_buffer, sizeof(client_buffer), 0)) > 0) {

        memcpy(me, client_buffer, sizeof(buffer));

        if (strcmp(me->command, "new_user") == 0) {
            insert_user(data->user_list, me->content);

            buffer[0] = '\0';
            strcat(buffer, "Users: \n");
            show_users(data->user_list, buffer);
            send(sock, buffer, sizeof(buffer), 0);
        }

        buffer[0] = '\0';
        strcat(buffer, "Client: ");
        strcat(buffer, me->content);
        send(sock, buffer, sizeof(buffer), 0);

    }

    if (read_size == 0) {
        puts("Client disconnected.");
        fflush(stdout);
    } else if (read_size == -1) {
        perror("recv failed!");
    }

    close(data->sock);

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
        if (strcmp(list->name[i], name) != 0 && !conf) {
            conf = 1;
        } else {
            new[j] = (char*) malloc(sizeof(char) * 512);
            new[j][0] = '\0';
            strcat(new[j], list->name[i]);
            j++;
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

