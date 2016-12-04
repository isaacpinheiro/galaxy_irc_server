#ifndef SERVER_CMD_H
#define SERVER_CMD_H

#define MAX_PENDING 5
#define BUFFER_SIZE 1024

typedef struct {
    char user_name[256];
    char command[256];
    char content[512];
} Message;

void *connection_handler(void *socket_desc);

#endif

