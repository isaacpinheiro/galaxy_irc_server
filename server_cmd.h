#ifndef SERVER_CMD_H
#define SERVER_CMD_H

#define MAX_PENDING 5
#define BUFFER_SIZE 1024

void *connection_handler(void *socket_desc);

#endif

