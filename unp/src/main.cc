/// =====================================================================================
/// 
///    @filename         :  test_main.cc
/// 
///    @description      :  
/// 
///    @version          :  1.0
///    @created          :  2014年09月20日 16时27分36秒
///    @revision         :  none
///    @compiler         :  g++
/// 
///    @author           :  Lei Yunfei (leiyunfei), yunfei_lei@126.com
///    @company          :  
/// 
/// =====================================================================================

#include <iostream>
#include "../inc/unp.h"

using std::cout;
using std::endl;

int main()
{
    union {
        short s;
        char c[sizeof(short)];
    } un;
    un.s = 0x0102;
    cout << CPU_VENDOR_OS << ":";
    if (sizeof(short) == 2)
    {
        if (un.c[0] == 1 && un.c[1] == 2)
            cout << "big-endian" << endl;
        else if (un.c[0] == 2 && un.c[1] == 1)
            cout << "little-endian" << endl;
        else
            cout << "unknown" << endl;
    }

    return 0;
}
