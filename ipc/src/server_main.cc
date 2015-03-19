// =====================================================================================
//
//       Filename:  server_main.cc
//
//    Description:  
//
//        Version:  1.0
//        Created:  2015年03月16日 14时49分50秒
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  leiyunfei (yun63), towardstheway@gmail.com
//   Organization:  
//
// =====================================================================================

#include "src/pipe/fifo.h"
#include "ipc.h"

void msg_server(int, int);

int main(int argc, char **argv)
{
    int readfd, writefd;

    if ((mkfifo(FIFO_1, FILE_MODE) < 0) && (errno != EEXIST))
        error_terminate("can't create %s", FIFO_1);
    if ((mkfifo(FIFO_2, FILE_MODE) < 0) && (errno != EEXIST))
    {
        unlink(FIFO_1);
        error_terminate("can't create %s", FIFO_2);
    }

    readfd = Open(FIFO_1, O_RDONLY, 0);
    writefd = Open(FIFO_2, O_WRONLY, 0);

    msg_server(readfd, writefd);

    return 0;
}
