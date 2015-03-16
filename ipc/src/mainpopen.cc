// =====================================================================================
//
//       Filename:  mainpopen.cc
//
//    Description:  
//
//        Version:  1.0
//        Created:  2015年03月16日 11时44分00秒
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
    char buffer[MAXLINE + 1], command[MAXLINE + 1];
    FILE *fp = NULL;

    memset(buffer, sizeof(buffer), 0);
    memset(command, sizeof(command), 0);

    Fgets(buffer, MAXLINE, stdin);
    int n = strlen(buffer);
    if (buffer[n-1] =='\n')
        n--;
    snprintf(command, sizeof(command), "cat %s", buffer);
    fp = Popen(command, "r");

    while (Fgets(buffer, MAXLINE, fp) != NULL)
        Fputs(buffer, stdout);

    Pclose(fp);

    return 0;
}
