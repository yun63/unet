// =====================================================================================
//
//       Filename:  msg_server.cc
//
//    Description:  
//
//        Version:  1.0
//        Created:  2015年03月19日 12时32分30秒
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  leiyunfei (yun63), towardstheway@gmail.com
//   Organization:  
//
// =====================================================================================

#include "msg.h"

void msg_server(int readfd, int writefd)
{
    FILE *fp = NULL;
    ssize_t n;
    struct Message msg;

    msg.msg_type = 1;
    if ((n = msg_recv(readfd, &msg)) == 0)
        error_quit("pathname misssing");
    msg.msg_data[n] = '\0';

    if ((fp = fopen(msg.msg_data, "r")) == NULL)
    {
        snprintf(msg.msg_data + n, sizeof(msg.msg_data) - n, ": can't open %s\n", strerror(errno));
        msg.msg_len = strlen(msg.msg_data);
        msg_send(writefd, &msg);
    }
    else
    {
        while (Fgets(msg.msg_data, MAX_MESSAGE_DATA_SIZE, fp) != NULL)
        {
            msg.msg_len = strlen(msg.msg_data);
            msg_send(writefd, &msg);
        }
        Fclose(fp);
    }

    msg.msg_len = 0;
    msg_send(writefd, &msg);
}
