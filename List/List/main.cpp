#include <stdio.h>

#include "List.h"

#define PICTURE "../dot/picture.png"
#define DOT_FILE "../dot/test.txt"

#define PICTURE_OPEN "start ..\\dot\\picture.png"
int main() 
{
    List * list = ListCtorDin();
    for (int i = 0; i <= 100; i++) {
        ListInsert(list, i);
    }
    Item * item = ListInsert(list, 111);
    for (int i = 90; i >= 30; i--) {
        ListDelete(list, i);    
    }

    ListDump(list, DOT_FILE, PICTURE);
    system(PICTURE_OPEN);

    ListDtorDin(list);
    return 0;
}