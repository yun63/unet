// =====================================================================================
//
//       Filename:  test.cc
//
//    Description:  
//
//        Version:  1.0
//        Created:  2015年03月18日 19时09分55秒
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  leiyunfei (yun63), towardstheway@gmail.com
//   Organization:  
//
// =====================================================================================

#include "ipc.h"

int main(int argc, char **argv)
{
    char buff[MAXLINE];
    memset(buff, sizeof(buff), 0);

    int fd = open("test.rb", O_RDONLY);
    size_t n = Readline(fd, buff, MAXLINE);
    printf("%d|%s", n, buff);

    return 0;
}
