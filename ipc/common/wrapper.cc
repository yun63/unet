// =====================================================================================
//
//       Filename:  wrapper.cc
//
//    Description:  常用的系统调用/函数库的封装
//
//        Version:  1.0
//        Created:  2015年03月12日 11时47分36秒
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  leiyunfei (yun63), towardstheway@gmail.com
//   Organization:  
//
// =====================================================================================

#include <stdarg.h>

#include "ipc.h"

void *Malloc(size_t size)
{
    void *ptr;
    if ((ptr = malloc(size)) == NULL)
        error_terminate("malloc error");
    return ptr;
}

void *Calloc(size_t n, size_t size)
{
    void *ptr;
    if ((ptr = calloc(n, size)) == NULL)
        error_terminate("calloc error");

    return ptr;
}

void Close(int fd)
{
    if (close(fd) == -1) 
        error_terminate("close error");
}


pid_t Fork(void)
{
    pid_t pid;
    if ((pid = fork()) == -1)
        error_terminate("fork error");
    return pid;
}

void Fstat(int fd, struct stat *ptr)
{
    if (fstat(fd, ptr) == -1)
        error_terminate("fstat error");
}

void Pipe(int *fds)
{
    if (pipe(fds) < 0)
        error_terminate("pipe error");
}

pid_t Waitpid(pid_t pid, int *ptr, int options)
{
    pid_t retpid;

    if ((retpid = waitpid(pid, ptr, options)) == -1)
        error_terminate("waitpid error");

    return retpid;
}

ssize_t Read(int fd, void *ptr, size_t bytes)
{
    ssize_t n;

    if ((n = read(fd, ptr, bytes)) == -1)
        error_terminate("read error");

    return n;
}

void Write(int fd, void *ptr, size_t bytes)
{
    if (write(fd, ptr, bytes) != bytes)
        error_terminate("write error");
}

char *Fgets(char *ptr, int n, FILE *stream)
{
    char *rptr;
    if ((rptr = fgets(ptr, n, stream)) == NULL && ferror(stream))
        error_terminate("fgets error");

    return rptr;
}

FILE *Fopen(const char *pathname, const char *mode)
{
    FILE *fp;
    if ((fp = fopen(pathname, mode)) == NULL)
            error_terminate("fopen error");

    return fp;
}

void Fputs(const char *ptr, FILE *stream)
{
    if (fputs(ptr, stream) == EOF)
        error_terminate("fputs error");
}

FILE *Popen(const char *command, const char *mode)
{
    FILE    *fp;
    if ((fp = popen(command, mode)) == NULL)
        error_terminate("popen error");
    return fp;
}

void Fclose(FILE *fp)
{
    if (fclose(fp) != 0)
        error_terminate("fclose error");
}

