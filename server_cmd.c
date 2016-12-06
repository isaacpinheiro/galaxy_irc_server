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

            User u;
            u.sock = sock;
            u.name[0] = '\0';
            strcat(u.name, buffer);
            insert_user(data->user_list, u);

        } else if (strcmp(client_buffer, "/list") == 0) {

            buffer[0] = '\0';
            strcat(buffer, "Users: \n");
            show_users(data->user_list, buffer);
            send(sock, buffer, sizeof(buffer), 0);

        } else if (strcmp(client_buffer, "/quit") == 0) {

            buffer[0] == '\0';
            recv(sock, buffer, sizeof(buffer), 0);
            data->user_list->user = remove_user(data->user_list, buffer);

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

void insert_user(UserList *list, User user)
{

    if (list->len == 0) list->user = (User*) malloc(sizeof(User));
    else list->user = (User*) realloc(list->user, (list->len + 1) * sizeof(User));

    list->user[list->len] = user;
    list->len++;

}

User *remove_user(UserList *list, char *name)
{

    if (list->len == 0) return NULL;

    User *new = (User*) malloc(sizeof(User) * (list->len-1));
    char conf = 0;
    int i, j;
    j = 0;

    for (i=0; i<list->len; i++) {
        if (strcmp(list->user[i].name, name) == 0 && !conf) {
            conf = 1;
        } else {
            new[j] = list->user[i];
            j++;
        }
    }

    if (conf) list->len--;
    free(list->user);

    return new;

}

void show_users(UserList *list, char *buffer)
{

    int i;

    for (i=0; i<list->len; i++) {
        strcat(buffer, list->user[i].name);
        if (i < list->len - 1) strcat(buffer, "\n");
    }

}

void change_nick(UserList *list, char *current_name, char *new_name)
{

    int i;

    for (i=0; i<list->len; i++) {
        if (strcmp(list->user[i].name, current_name) == 0) {
            list->user[i].name[0] = '\0';
            strcat(list->user[i].name, new_name);
            break;
        }
    }

}

