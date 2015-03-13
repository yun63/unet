// =====================================================================================
//
//       Filename:  mainpipe.cc
//
//    Description:  进程间通信-管道
//
//        Version:  1.0
//        Created:  2015年03月12日 11时17分58秒
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  leiyunfei (yun63), towardstheway@gmail.com
//   Organization:  
//
// =====================================================================================

#include "ipc.h"

void client(int, int);
void server(int, int);

int main(int argc, char **argv)
{
    int pipe1[2], pipe2[2];

    pid_t child_pid;

    Pipe(pipe1);
    Pipe(pipe2);

    if ((child_pid = Fork()) == 0)
    {
        /* 子进程 */
        Close(pipe1[1]);
        Close(pipe2[0]);

        server(pipe1[0], pipe2[1]);
        exit(0);
    }

    /* 父进程 */
    Close(pipe1[0]);
    Close(pipe2[1]);

    client(pipe2[0], pipe1[1]);

    /* 等待子进程退出 */
    Waitpid(child_pid, NULL, 0);

    return 0;
}
