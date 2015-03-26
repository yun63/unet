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
    int c, flags;
    mqd_t   mqd;

    flags = O_RDWR | O_CREAT;

    while ((c = Getopt(argc, argv, "e")) != -1)
    {
        switch (c)
        {
            case 'e':
            {
                flags |= O_EXCL;
                break;
            }
        }
    };

    if (optind != argc - 1)
        error_quit("usage: mqcreate [ -e ] <name>");

    mqd = Mq_open(argv[optind], flags, FILE_MODE, NULL);

    Mq_close(mqd);

    return 0;
}
