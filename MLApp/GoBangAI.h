#ifndef _GOBANGAI_H
#define _GOBANGAI_H
#ifdef __cplusplus
extern "C" {
#endif
#include "CLib/Stack.h"
#include "CLib/LinkList.h"

typedef struct pos
{
    int x;
    int y;
}pos;


typedef struct scoreshape
{
    //(50, ((0, 1, 1, 0, 0),(1,1,0,0,0)),(1,0))
    int score_val;
    pos pos_arr[10];
    pos direct;
    int pos_arr_size;
}scoreshape;

/*struct for the global score constant*/
typedef struct scorest
{
    int scorest_val;
    int scorest_arr[6];
    int scorest_size;
}scorest;

void GoBang_Main();


#ifdef __cplusplus
}
#endif
#endif  /* _GOBANGAI_H */
