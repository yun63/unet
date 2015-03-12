// =====================================================================================
//
//       Filename:  server.cc
//
//    Description:  服务端程序
//
//        Version:  1.0
//        Created:  2015年03月12日 18时04分01秒
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  leiyunfei (yun63), towardstheway@gmail.com
//   Organization:  
//
// =====================================================================================

#include "ipc.h"

void server(int readfd, int writefd)
{
    int     fd;
    ssize_t n;
    char    buff[MAXLINE];

    /* 从IPC管道里读取数据 */
    if ((n = Read(readfd, buff, MAXLINE)) == 0)
        error_quit("end-of-file while reading pathname");
    /* 文件名终止符 */
    buff[n] = '\0';

    if ((fd = open(buff, O_RDONLY)) < 0)
    {
        /* 必须通知客户端 */
        snprintf(buff + n, sizeof(buff) - n, ": can't open, %s\n", strerror(errno));
        n = strlen(buff);
        Write(writefd, buff, n);
    }
    else
    {
        while ((n = Read(fd, buff, MAXLINE)) > 0)
            Write(writefd, buff, n);
        Close(fd);
    }
}
