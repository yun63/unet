// =====================================================================================
//
//       Filename:  msg_handler.cc
//
//    Description:  消息发送/接收函数
//
//        Version:  1.0
//        Created:  2015年03月19日 11时50分16秒
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  leiyunfei (yun63), towardstheway@gmail.com
//   Organization:  
//
// =====================================================================================

#include "msg.h"

ssize_t msg_send(int fd, struct Message *mptr)
{
    return write(fd, mptr, MESSAGE_HEADER_SIZE + mptr->msg_len);
}

ssize_t msg_recv(int fd, struct Message *mptr)
{
    size_t  len;
    ssize_t n;

    if ((n = Read(fd, mptr, MESSAGE_HEADER_SIZE)) == 0)
        return 0;
    else if (n != MESSAGE_HEADER_SIZE)
        error_quit("message header: expected %d, got %d", MESSAGE_HEADER_SIZE, n);
    
    if ((len = mptr->msg_len) > 0)
    {
        if ((n = Read(fd, mptr->msg_data, len)) != len)
        {
            error_quit("message data: expected %d, got %d", len, n);
        }
    }

    return len;
}
