#ifndef SERVER_CMD_H
#define SERVER_CMD_H

#define MAX_PENDING 5
#define BUFFER_SIZE 1024

typedef struct Message {
    char user_name[256];
    char command[256];
    char content[512];
} Message;

typedef struct User {
    int len;
    char **name;
} User;

void *connection_handler(void *socket_desc);
void insert_user(User *list, char *name);
char **remove_user(User *list, char *name);
void show_users(User *list, char *buffer);

#endif

