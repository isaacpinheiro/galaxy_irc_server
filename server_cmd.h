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

typedef struct ThreadArgs {
    int sock;
    User *user_list;
} ThreadArgs;

void *connection_handler(void *args);
void insert_user(User *list, char *name);
char **remove_user(User *list, char *name);
void show_users(User *list, char *buffer);

#endif

