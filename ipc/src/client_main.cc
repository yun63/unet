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

void client(int, int);

int main(int argc, char **argv)
{
    int readfd, writefd;

    writefd = Open(FIFO_1, O_WRONLY, 0);
    readfd = Open(FIFO_2, O_RDONLY, 0);

    client(readfd, writefd);

    Close(readfd);
    Close(writefd);

    Unlink(FIFO_1);
    Unlink(FIFO_2);

    return 0;
}
