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

    while ((read_size = recv(sock, client_buffer, sizeof(client_buffer), 0)) > 0) {

        if (strcmp(client_buffer, "/new_user") == 0) {

            buffer[0] == '\0';
            recv(sock, buffer, sizeof(buffer), 0);
            insert_user(data->user_list, buffer);

        } else if (strcmp(client_buffer, "/list") == 0) {

            buffer[0] = '\0';
            strcat(buffer, "Users: \n");
            show_users(data->user_list, buffer);
            send(sock, buffer, sizeof(buffer), 0);

        } else if (strcmp(client_buffer, "/quit") == 0) {

            buffer[0] == '\0';
            recv(sock, buffer, sizeof(buffer), 0);
            data->user_list->name = remove_user(data->user_list, buffer);

        } else if (strcmp(client_buffer, "/kill") == 0) {

            char k_name[1024];
            k_name[0] = '\0';

            buffer[0] == '\0';
            recv(sock, buffer, sizeof(buffer), 0);
            strcat(k_name, buffer);

            buffer[0] = '\0';
            strcat(buffer, "Not implemented.");
            send(sock, buffer, sizeof(buffer), 0);

            // TODO

        } else if (strcmp(client_buffer, "/nick") == 0) {

            char c_name[1024];
            c_name[0] = '\0';

            buffer[0] == '\0';
            recv(sock, buffer, sizeof(buffer), 0);
            strcat(c_name, buffer);

            buffer[0] == '\0';
            recv(sock, buffer, sizeof(buffer), 0);
            change_nick(data->user_list, c_name, buffer);

        } else {

            buffer[0] = '\0';
            strcat(buffer, client_buffer);
            send(sock, buffer, sizeof(buffer), 0);

        }

        client_buffer[0] = '\0';

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
        if (strcmp(list->name[i], name) == 0 && !conf) {
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
        if (i < list->len - 1) strcat(buffer, "\n");
    }

}

void change_nick(User *list, char *current_name, char *new_name)
{

    int i;

    for (i=0; i<list->len; i++) {
        if (strcmp(list->name[i], current_name) == 0) {
            list->name[i][0] = '\0';
            strcat(list->name[i], new_name);
            break;
        }
    }

}

