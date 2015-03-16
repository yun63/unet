// =====================================================================================
// 
// @filename         :  main.cc
// @description      :  

// @version          :  1.0
// @created          :  2014年12月09日 17时13分26秒
// @revision         :  none
// @compiler         :  g++
// @author           :  Lei Yunfei (leiyunfei), yunfei_lei@126.com
// @company          :  
// 
// =====================================================================================

#include "ipc.h"

int main(int argc, char **argv)
{
    int pipe[2];
    int n;
    char buffer[MAXLINE + 1];
    pid_t child_pid;

    Pipe(pipe);

    if ((child_pid = Fork()) == 0)
    {
        sleep(3);

        if ((n = Read(pipe[0], buffer, MAXLINE)) <= 0)
            error_terminate("child: read retruned %d", n);
        printf("child read %s\n", buffer);
        Write(pipe[0], buffer, strlen(buffer));
        exit(0);
    }

    Fgets(buffer, MAXLINE, stdin);

    Write(pipe[1], buffer, strlen(buffer));

    if ((n = Read(pipe[1], buffer, MAXLINE)) <= 0)
        error_terminate("parent: read returned %d", n);
    printf("parent read %s\n", buffer);

    return 0;
}
