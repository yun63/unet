// =====================================================================================
//
//       Filename:  error_handler.cc
//
//    Description:  常用的错误处理附注函数
//
//        Version:  1.0
//        Created:  2015年03月12日 11时56分28秒
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  leiyunfei (yun63), towardstheway@gmail.com
//   Organization:  
//
// =====================================================================================

#include <stdarg.h>
#include <syslog.h>                             // for syslog() 

#include "ipc.h"

int daemon_proc;                                // set nonzero by daemon_init() 

static void error_doit(int, int, const char *, va_list);

// 与系统调用相关的非致命性错误函数，打印错误信息并返回
void error_return(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    error_doit(1, LOG_INFO, fmt, ap);
    va_end(ap);

    return;
}

// 与系统调用相关的致命性错误函数，打印错误信息并终止调用
void error_terminate(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    error_doit(1, LOG_ERR, fmt, ap);
    va_end(ap);

    exit(1);
}

// 与系统调用相关的致命性错误函数，打印错误，dump core并且终止
void error_dump(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    error_doit(1, LOG_ERR, fmt, ap);
    va_end(ap);

    // dump core and terminate
    abort();        
    exit(1);
}

void error_message(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    error_doit(0, LOG_INFO, fmt, ap);
    va_end(ap);

    return;
}

void error_quit(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    error_doit(0, LOG_ERR, fmt, ap);
    va_end(ap);

    exit(1);
}

static void error_doit(int errnoflag, int level, const char *fmt, va_list ap)
{
    int errno_save;
    char buf[MAXLINE];

    errno_save = errno;

    vsnprintf(buf, sizeof(buf), fmt, ap);

    int n = strlen(buf);
    if (errnoflag)
    {
        snprintf(buf + n, sizeof(buf) - n, ": %s", strerror(errno_save));
    }

    strcat(buf, "\n");

    if (daemon_proc)
    {
        syslog(level, buf, ap);
    }
    else
    {
        fflush(stdout);
        fputs(buf, stderr);
        fflush(stderr);
    }

    return;
}

