
#ifndef  MESSAGE_INC
#define  MESSAGE_INC

#include "ipc.h"

#define MAX_MESSAGE_DATA_SIZE   (PIPE_BUF - 2 * sizeof(long))
#define MESSAGE_HEADER_SIZE     (sizeof(struct Message) - MAX_MESSAGE_DATA_SIZE)

struct Message 
{
    long    msg_len;
    long    msg_type;
    char    msg_data[MAX_MESSAGE_DATA_SIZE];
};

ssize_t msg_send(int, struct Message *);
void    Msg_send(int, struct Message *);
ssize_t msg_recv(int, struct Message *);
ssize_t Msg_recv(int, struct Message *);

#endif   // ----- #ifndef MESSAGE_INC  ----- 
