// =====================================================================================
//
//       Filename:  msg_client.cc
//
//    Description:  
//
//        Version:  1.0
//        Created:  2015年03月19日 12时32分23秒
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  leiyunfei (yun63), towardstheway@gmail.com
//   Organization:  
//
// =====================================================================================

#include "src/pipe/msg.h"

void msg_client(int readfd, int writefd)
{
    size_t len;
    ssize_t n;
    struct Message msg;

    /* read pathname */
    Fgets(msg.msg_data, MAX_MESSAGE_DATA_SIZE, stdin);
    len = strlen(msg.msg_data);
    if (msg.msg_data[len-1] == '\n')
        len--;
    msg.msg_len = len;
    msg.msg_type = 1;

    msg_send(writefd, &msg);

    /* read from IPC, write to standard output */
    while ((n = msg_recv(readfd, &msg)) > 0)
        Write(STDOUT_FILENO, msg.msg_data, n);
}
