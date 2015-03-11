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

#include "inc/ipc.h"

int main(int argc, char **argv)
{
    struct stat st;
    if (argc != 2)
    {
        printf("usage: ftok <pathname>");
        exit(-1);
    }

    if (stat(argv[1], &st) == -1)
    {
        printf("stat error\n");
        exit(-1);
    }

    printf("%d\n", 	HAVE_SYS_MSG_H);

    printf("st_dev: %lx, st_ino: %lx, key: %x\n", 
            (u_long)st.st_dev, (u_long)st.st_ino, ftok(argv[1], 0x57));

    int i, msgid;

    for (i = 0; i < 10; i++)
    {
        msgid = msgget(IPC_PRIVATE, SVMSG_MODE | IPC_CREAT);
        printf("msgid = %d\n", msgid);
        msgctl(msgid, IPC_RMID, NULL);
    }

    return 0;
}
