// =====================================================================================
//
//       Filename:  fifo_server.cc
//
//    Description:  
//
//        Version:  1.0
//        Created:  2015年03月17日 15时41分56秒
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  leiyunfei (yun63), towardstheway@gmail.com
//   Organization:  
//
// =====================================================================================

#include "ipc.h"
#include "src/pipe/fifo.h"

void server(int, int);

int main(int argc, char **argv)
{
    int readfifo, writefifo, dummyfd, fd;
    char *ptr, buff[MAXLINE + 1], fifoname[MAXLINE + 1];
    pid_t   pid;
    ssize_t n;

    /* 创建服务器管道 */
    if ((mkfifo(SERV_FIFO, FILE_MODE) < 0) && (errno != EEXIST))
    {
        error_terminate("can't create %s", SERV_FIFO);
    }

    /* 打开服务器管道用于读／写数据 */
    readfifo = Open(SERV_FIFO, O_RDONLY, 0);
    dummyfd = Open(SERV_FIFO, O_WRONLY, 0); /* 从不使用 */

    while ((n = Readline(readfifo, buff, MAXLINE)) > 0)
    {
        if (buff[n - 1] == '\n')
            n--;                                /* 删除换行符 */
        buff[n - 1] = '\0';                     /* null terminate */

        if ((ptr = strchr(buff, ' ')) == NULL)
        {
            error_message("baddly request: %s", buff);
            continue;
        }

        *ptr++ = 0;                             /* null terminate PID, ptr = pathname */
        pid = atol(buff);
        snprintf(fifoname, sizeof(fifoname), "/tmp/fifo.%ld", (long)pid);

        if ((writefifo = Open(fifoname, O_WRONLY, 0)) < 0)
        {
            error_message("can't open %s", fifoname);
            continue;
        }

        if ((fd = open(ptr, O_RDONLY | O_NONBLOCK)) < 0)
        {
            /* 打开文件失败，必须通知客户端 */
            snprintf(buff + n, sizeof(buff) - n, "can't open, %s\n", strerror(errno));
            n = strlen(buff);
            Write(writefifo, buff, n);
            Close(writefifo);
        }
        else
        {
            while ((n = Read(fd, buff, MAXLINE)) > 0)
            {
                Write(writefifo, buff, n);
            }
            Close(fd);
            Close(writefifo);
        }

    }

    return 0;
}
