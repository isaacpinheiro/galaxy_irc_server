#ifndef SERVER_CMD_H
#define SERVER_CMD_H

#define MAX_PENDING 5
#define BUFFER_SIZE 1024

typedef struct User {
    int sock;
    char name[256];
} User;

typedef struct UserList {
    int len;
    User *user;
} UserList;

typedef struct ThreadArgs {
    int sock;
    UserList *user_list;
} ThreadArgs;

typedef struct Message {
    char user_name[256];
    char command[256];
    char content[512];
} Message;

void *connection_handler(void *args);
void insert_user(UserList *list, User user);
User *remove_user(UserList *list, char *name);
void show_users(UserList *list, char *buffer);
void change_nick(UserList *list, char *current_name, char *new_name);
void send_all(UserList *list, char *buffer);
void kill_user(UserList *list, char *name);

#endif

