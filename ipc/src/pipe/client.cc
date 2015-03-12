// =====================================================================================
//
//       Filename:  client.cc
//
//    Description:  客户端程序
//
//        Version:  1.0
//        Created:  2015年03月12日 18时00分47秒
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  leiyunfei (yun63), towardstheway@gmail.com
//   Organization:  
//
// =====================================================================================

#include "ipc.h"

void client(int readfd, int writefd)
{
    size_t  len;
    ssize_t n;
    char buff[MAXLINE];
    
    Fgets(buff, MAXLINE, stdin);
    len = strlen(buff);

    if (buff[len - 1] == '\n')
        len--;

    /* 向IPC管道写数据 */
    Write(writefd, buff, len);

    while ((n = Read(readfd, buff, MAXLINE)) > 0)
        Write(STDOUT_FILENO, buff, n);
}
