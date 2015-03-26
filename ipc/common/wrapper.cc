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

int Open(const char *pathname, int oflag, ...)
{
    int fd;
    va_list ap;
    mode_t  mode;

    if (oflag & O_CREAT)
    {
        va_start(ap, oflag);
        va_arg(ap, va_mode_t);
        if ((fd = open(pathname, oflag, mode)) == -1)
        {
            error_terminate("open error");
        }
    }
    else
    {
        if ((fd = open(pathname, oflag)) == -1)
        {
            error_terminate("open error");
        }
    }

    return fd;
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

int Pclose(FILE *fp)
{
    int status;
    if ((status = pclose(fp)) == -1)
        error_terminate("pclose error");

    return status;
}

void Fclose(FILE *fp)
{
    if (fclose(fp) != 0)
        error_terminate("fclose error");
}

void Unlink(const char *pathname)
{
    if (unlink(pathname) == -1)
    {
        error_terminate("unlink error %s", pathname);
    }
}

ssize_t readline(int fd, void *vptr, size_t maxlen)
{
    int i, readbypes;
    char c;
    char *ptr = (char *)vptr;

    for (int i = 0; i < maxlen - 1; ++i)
    {
        if ((readbypes = read(fd, &c, 1)) == 1)
        {
            *ptr++ = c;
            if (c == '\n') break;
        }
        else if (readbypes == 0)
        {
            if (i == 0) 
            {
                return 0;
            }
            else 
            {
                break;
            }
        }
        else
        {
            return -1;
        }
    }

    *ptr = 0;   /* null terminate like fgets() */

    return i;
}

ssize_t Readline(int fd, void *ptr, size_t maxlen)
{
    ssize_t n = 0;

    if ((n = readline(fd, ptr, maxlen)) < 0)
    {
        error_terminate("readline error");
    }

    return n;
}

mqd_t Mq_open(const char *pathname, int oflag, ...)
{
    mqd_t mqd;
    va_list ap;
    mode_t mode;
    struct mq_attr *attr;

    if (oflag & O_CREAT)
    {
        va_start(ap, oflag);
        mode = va_arg(ap, va_mode_t);
        attr = va_arg(ap, struct mq_attr *);
        if ((mqd = mq_open(pathname, oflag, mode, attr)) == (mqd_t)-1)
        {
            error_terminate("mq_open error: %s", pathname);
            va_end(ap);
        }
        else
        {
            if ((mqd = mq_open(pathname, oflag)) == (mqd_t)-1)
            {
                error_terminate("mq_open: %s", pathname);
            }
        }
    }

    return mqd;
}

void Mq_close(mqd_t mqd)
{
    if (mq_close(mqd) == -1)
    {
        error_terminate("mq_close error");
    }
}

void Mq_unlink(const char *pathname)
{
    if (mq_unlink(pathname) == -1)
    {
        error_terminate("mq_unlink error");
    }
}

int Getopt(int argc, char * const *argv, const char *str)
{
    int opt;
    if ((opt = getopt(argc, argv, str)) == '?')
    {
        exit(1);
    }

    return opt;
}

