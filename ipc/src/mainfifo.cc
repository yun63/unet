// =====================================================================================
//
//       Filename:  mainfifo.cc
//
//    Description:  命名管道实现进程间通信
//
//        Version:  1.0
//        Created:  2015年03月16日 12时05分23秒
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  leiyunfei (yun63), towardstheway@gmail.com
//   Organization:  
//
// =====================================================================================

#include "ipc.h"
#include "src/pipe/fifo.h"

int server(int, int);
int client(int, int);

int main(int argc, char **argv)
{
    int readfd, writefd;
    pid_t   child_pid;

    if ((mkfifo(FIFO_1, FILE_MODE) < 0) && (errno != EEXIST))
    {
        error_terminate("can't create %s", FIFO_1);
    }

    if ((mkfifo(FIFO_2, FILE_MODE) < 0) && (errno != EEXIST))
    {
        unlink(FIFO_1);
        error_terminate("can't create %s", FIFO_2);
    }

    if ((child_pid = Fork()) == 0)
    {
        readfd = Open(FIFO_1, O_RDONLY, 0);
        writefd = Open(FIFO_2, O_WRONLY, 0);

        server(readfd, writefd);
        exit(0);
    }

    writefd = Open(FIFO_1, O_WRONLY, 0);
    readfd = Open(FIFO_2, O_RDONLY, 0);

    client(readfd, writefd);

    Waitpid(child_pid, NULL, 0);

    Close(readfd);
    Close(writefd);

    Unlink(FIFO_1);
    Unlink(FIFO_2);

    return 0;
}
