// =====================================================================================
//
//       Filename:  fifo_client.cc
//
//    Description:  
//
//        Version:  1.0
//        Created:  2015年03月17日 15时42分42秒
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  leiyunfei (yun63), towardstheway@gmail.com
//   Organization:  
//
// =====================================================================================

#include "ipc.h"
#include "src/pipe/fifo.h"

void client(int, int);

int main(int argc, char **argv)
{
    int readfifo, writefifo;
    char *ptr, fifoname[MAXLINE], buff[MAXLINE];
    ssize_t n;

    pid_t pid = getpid();
    snprintf(fifoname, sizeof(fifoname), "/tmp/fifo.%ld", (long)pid);
    if ((mkfifo(fifoname, FILE_MODE) < 0) && (errno != EEXIST))
    {
        error_terminate("can't create %s", fifoname);
    }

    /* 用pid和空格填充buff */
    snprintf(buff, sizeof(buff), "%ld ", (long)pid);
    size_t len = strlen(buff);
    ptr = buff + len;

    /* 从标准输入读取路径 */
    Fgets(ptr, MAXLINE - len, stdin);
    len = strlen(buff); /* fgets()保证在字符串末尾包含null */
    /* 打开服务器命名管道，并将pid和pathname写入该管道 */
    writefifo = Open(SERV_FIFO, O_WRONLY, 0);
    Write(writefifo, buff, len);
    /* 打开客户端管道,读取来自服务器发来的数据 */
    readfifo = Open(fifoname, O_RDONLY, 0);
    /* 读取数据 */
    while ((n = Read(readfifo, buff, MAXLINE)) > 0)
    {
        Write(STDOUT_FILENO, buff, n);
    }

    Close(readfifo);
    Unlink(fifoname);

    return 0;
}
