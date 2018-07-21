/*  This file is part of MLApp
 *
 *  Copyright (c) 2017-2018, MR.Black. All rights reserved.
 *  
 *  See my github for details. https://github.com/Demonmikalis/MLApp
 *
 *  author: MR.Black <demonmikalis@gmail.com> 
 * 
 *  Use of this source code is governed by a BSD-style license that can be found in the LICENSE file.
 */

#include "GoBangAI.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

static int COLUMN = 15;
static int ROW = 15;
static const int DEPTH = 3;

/*stores the AI's dropped position*/
LinkList *list1 = NULL;
/*stores the Player's dropped position*/
LinkList *list2 = NULL;
/*stores the Player's and AI's dropped position*/
LinkList *list3 = NULL;
/*stores the total chessboard position*/
LinkList *list_all = NULL;

pos next_point;

static scorest global_shape_score[15];
static double ratio = 1.0;

static void init_global_shape_score()
{
    /* make a score table */
    int scoreArr[15][7] = {{50, 0, 1, 1, 0, 0,-1},
                          {50, 0, 0, 1, 1, 0, -1},
                          {200, 1, 1, 0, 1, 0, -1},
                          {500, 0, 0, 1, 1, 1, -1},
                          {500, 1, 1, 1, 0, 0, -1},
                          {5000, 0, 1, 1, 1, 0,-1},
                          {5000, 0, 1, 0, 1, 1, 0},
                          {5000, 0, 1, 1, 0, 1, 0},
                          {5000, 1, 1, 1, 0, 1, -1},
                          {5000, 1, 1, 0, 1, 1, -1},
                          {5000, 1, 0, 1, 1, 1, -1},
                          {5000, 1, 1, 1, 1, 0, -1},
                          {5000, 0, 1, 1, 1, 1, -1},
                          {50000, 0, 1, 1, 1, 1, 0},
                          {99999999, 1, 1, 1, 1, 1,-1}};
    int i,j;
    for(i=0;i<15;i++)
    {
        global_shape_score[i].scorest_val = scoreArr[i][0];
        for(j=1;j<=5;j++)
        {
            global_shape_score[i].scorest_arr[j-1] = scoreArr[i][j];
        }
        global_shape_score[i].scorest_size = 5;
        //check the last element
        if(scoreArr[i][6]!=-1)
        {
            global_shape_score[i].scorest_arr[5] = scoreArr[i][6];
            global_shape_score[i].scorest_size++;
        }
    }
}


/**
 * @brief check whether pos pt in list
 */
static int isPosInList(pos pt, LinkList *list)
{
    if(list==NULL) return -1;
    int ret = 0;
    LinkListIterator *it = createLinkListIterator(list);
    while(LinkListIteratorHasNext(it))
    {
        pos *elem = (pos*)LinkListIteratorNext(it);
        if(elem->x == pt.x && elem->y == pt.y)
        {
            ret = 1;
            break;
        }
    }
    freeLinkListIterator(it);
    return ret;
}

/**
 * @brief check whether the arr is equal
 */
static int isArrEqual(int *a, int *b, int sz)
{
    int i=0,ret=1;
    for(i=0;i<sz;++i)
    {
        if(a[i]!=b[i])
        {
            ret=0;
            break;
        }
    }
    return ret;
}


/**
 * @brief find the first occurrence index that a pos elem in the linklist
 * @return the first occurrence index
 */
static int findPosInList(pos pt, LinkList *list)
{
    if(list==NULL) return -1;
    int ret = 0;
    LinkListIterator *it = createLinkListIterator(list);
    while(LinkListIteratorHasNext(it))
    {
        pos *elem = (pos*)LinkListIteratorNext(it);
        if(elem->x == pt.x && elem->y == pt.y)
        {
            break;
        }
        ret++;
    }
    freeLinkListIterator(it);
    return ret;
}

/**
 * @brief compute the list difference between A,B (elem in A not B)
 * and put the result in res
 * @param A: LinkList contains pos (x,y) 
 * @param B: LinkList contains pos (x,y) 
 * @param res: LinkList contains pos (x,y), the output
 */
static void posListDifference(LinkList *A, LinkList *B, LinkList *res)
{
    LinkListIterator *it = createLinkListIterator(A);
    while(LinkListIteratorHasNext(it))
    {
         pos *elem = (pos*)LinkListIteratorNext(it);
         pos tmp = {.x=elem->x,.y=elem->y};
         if(isPosInList(tmp,B))
         {
             continue;
         }else{
             pos *pt = (pos*)malloc(sizeof(pos));
             pt->x = elem->x;
             pt->y = elem->y;
             LinkListInsertDataAtLast(res,pt);
         }
    }
    freeLinkListIterator(it);
}


static int hasNeighbour(pos pt)
{
    if(list3==NULL)
    {
        printf("Error in hasNeighbour: List3 is NULL\n");
        return -1;
    }
    int i,j;
    for(i=-1;i<2;i++)
    {
        for(j=-1;j<2;j++)
        {
            if(j==0 && i==0) continue;
            pos tmp = {.x=pt.x+i,.y=pt.y+j};
            if(isPosInList(tmp,list3))
            {
                return 1;
            }
        }
    }
    return 0;
}


static int game_win(LinkList *list)
{
    int m,n;
    for(m=0;m<COLUMN;++m)
    {
        for(n=0;n<ROW;++n)
        {
            if(n<ROW-4)
            {
                pos p1 = {m,n}; pos p2 = {m,n+1};
                pos p3 = {m,n+2}; pos p4 = {m,n+3};
                pos p5 = {m,n+4};
                if(isPosInList(p1,list) && isPosInList(p2,list) && isPosInList(p3,list)
                    && isPosInList(p4,list) && isPosInList(p5,list))
                {
                    return 1;
                }
            }if (m<COLUMN-4)
            {
                pos p1 = {m,n}; pos p2 = {m+1,n};
                pos p3 = {m+2,n}; pos p4 = {m+3,n};
                pos p5 = {m+4,n};
                if(isPosInList(p1,list) && isPosInList(p2,list) && isPosInList(p3,list)
                    && isPosInList(p4,list) && isPosInList(p5,list))
                {
                    return 1;
                }
            }if (m<COLUMN-4 && n<ROW-4)
            {
                pos p1 = {m,n}; pos p2 = {m+1,n+1};
                pos p3 = {m+2,n+2}; pos p4 = {m+3,n+3};
                pos p5 = {m+4,n+4};
                if(isPosInList(p1,list) && isPosInList(p2,list) && isPosInList(p3,list)
                    && isPosInList(p4,list) && isPosInList(p5,list))
                {
                    return 1;
                }
            }if (m<COLUMN-4 && n>3)
            {
                pos p1 = {m,n}; pos p2 = {m+1,n-1};
                pos p3 = {m+2,n-2}; pos p4 = {m+3,n-3};
                pos p5 = {m+4,n-4};
                if(isPosInList(p1,list) && isPosInList(p2,list) && isPosInList(p3,list)
                    && isPosInList(p4,list) && isPosInList(p5,list))
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}


static void order(LinkList *blank_list)
{
    if(list3==NULL) return;
    pos *last_pt = LinkListGetDataAtLast(list3);
    int i,j;
    for(i=-1;i<2;i++)
    {
        for(j=-1;j<2;j++)
        {
            if(j==0 && i==0) continue;
            pos tmp = {.x=last_pt->x+i,.y=last_pt->y+j};
            if(isPosInList(tmp,blank_list))
            {
                int idx = findPosInList(tmp,blank_list);
                //printf("idx=%d\n",idx);
                LinkListRemoveDataAt(blank_list,idx);
                pos *tmp_copy = (pos*)malloc(sizeof(pos));
                tmp_copy->x = tmp.x; tmp_copy->y = tmp.y;
                LinkListInsertDataAt(blank_list,tmp_copy,0);
            }
        }
    }
}



int cal_score(int m, int n, int x_decrict, int y_derice, 
              LinkList *enemy_list, LinkList *my_list, LinkList **score_all_arr)
{
    int add_score = 0;
    scoreshape *max_score_shape = (scoreshape*)malloc(sizeof(scoreshape));
    max_score_shape->score_val = 0;
    max_score_shape->pos_arr_size = 0;
    int i,j;
    // if the score shape already exists at the current direction
    // skip
    LinkListIterator *it = createLinkListIterator(*score_all_arr);
    while(LinkListIteratorHasNext(it))
    {
       scoreshape *elem = (scoreshape*) LinkListIteratorNext(it);
       int pos_sz = elem->pos_arr_size;
       pos direct = elem->direct;
       for(i=0;i<pos_sz;++i)
       {
           pos pt = elem->pos_arr[i];
           if(pt.x==m && pt.y==n && direct.x==x_decrict && direct.y==y_derice)
           {
               return 0;
           }
       }
    }
    freeLinkListIterator(it);
    
    int offset = 0;
    for(offset=-5;offset<1;++offset)
    {
        int pos_tmp_arr[6];
        for(i=0;i<6;i++)
        {
            pos pos_tmp_val = {.x=m + (i + offset) * x_decrict, .y=n + (i + offset) * y_derice};
            if(isPosInList(pos_tmp_val,enemy_list))
            {
                pos_tmp_arr[i]=2;
            }else if(isPosInList(pos_tmp_val,my_list))
            {
                pos_tmp_arr[i]=1;
            }else{
                pos_tmp_arr[i]=0;
            }
        }
        int tmp_shap5[5] = {pos_tmp_arr[0], pos_tmp_arr[1], pos_tmp_arr[2], pos_tmp_arr[3], pos_tmp_arr[4]};
        int tmp_shap6[6] = {pos_tmp_arr[0], pos_tmp_arr[1], pos_tmp_arr[2], 
            pos_tmp_arr[3], pos_tmp_arr[4], pos_tmp_arr[5]};
        
        // access the element in global_shape_score
        const int global_shape_score_row = 15;
        for(i=0;i<global_shape_score_row;++i)
        {
            scorest tmp_scorest = global_shape_score[i];
            int score = tmp_scorest.scorest_val;
            int *score_array = tmp_scorest.scorest_arr;
            int ret_tmp = 0;
            if(tmp_scorest.scorest_size==5)
            {
                ret_tmp = isArrEqual(score_array,tmp_shap5,5);
            }else if (tmp_scorest.scorest_size==6)
            {
                ret_tmp = isArrEqual(score_array,tmp_shap6,6);
            }
            // whether score_array==tmp_shap5 or tmp_shap6
            if(ret_tmp)
            {
                if(score>max_score_shape->score_val)
                {
                    max_score_shape->score_val = score;
                    pos max_score_pos[6] = {{m + (0+offset) * x_decrict,n + (0+offset) * y_derice},
                        {m + (1+offset) * x_decrict, n + (1+offset) * y_derice},
                        {m + (2+offset) * x_decrict, n + (2+offset) * y_derice},
                        {m + (3+offset) * x_decrict, n + (3+offset) * y_derice},
                        {m + (4+offset) * x_decrict, n + (4+offset) * y_derice},
                        {x_decrict,y_derice}
                    };
                    int k;
                    for(k=0;k<5;++k)
                    {
                        max_score_shape->pos_arr[k] = max_score_pos[k];
                    }
                    max_score_shape->direct = max_score_pos[5];
                    max_score_shape->pos_arr_size = 5;
                }
            }
        }
        
    }
    
    if(max_score_shape->pos_arr_size>0)
    {
        LinkListIterator *it2 = createLinkListIterator(*score_all_arr);
        while(LinkListIteratorHasNext(it))
        {
            scoreshape *elem = (scoreshape*) LinkListIteratorNext(it2);
            int pos_sz = elem->pos_arr_size; int k;
            pos pt1,pt2;
            for(j=0;j<pos_sz;++j)
            {
                pt1 = elem->pos_arr[j];
                for(k=0;k<max_score_shape->pos_arr_size;++k)
                {
                    pt2 = max_score_shape->pos_arr[k];
                    if(pt1.x==pt2.x && pt1.y==pt2.y && max_score_shape->score_val>10
                        && elem->score_val>10)
                    {
                        add_score += max_score_shape->score_val + elem->score_val;
                    }
                }
            }
            
        }
        freeLinkListIterator(it2);
        // insert max_score_shape to linklist score_all_arr
        LinkListInsertDataAtLast(*score_all_arr,max_score_shape);
    }
    
    return add_score+max_score_shape->score_val;
}

double evaluation(int isAI)
{
    double total_score = 0;
    LinkList *enemy_list = NULL;
    LinkList *my_list = NULL;
    int my_score=0,enemy_score=0;
    if(isAI)
    {
        enemy_list = list2;
        my_list = list1;
    }else{
        enemy_list = list1;
        my_list = list2;
    }
    LinkList *score_all_arr = createLinkList();
    LinkList *score_all_arr_enemy = createLinkList();
    LinkListIterator *it = createLinkListIterator(my_list);
    while(LinkListIteratorHasNext(it))
    {
        pos *elem = (pos*)LinkListIteratorNext(it);
        int m = elem->x;
        int n = elem->y;
        my_score += cal_score(m, n, 0, 1, enemy_list, my_list, &score_all_arr);
        my_score += cal_score(m, n, 1, 0, enemy_list, my_list, &score_all_arr);
        my_score += cal_score(m, n, 1, 1, enemy_list, my_list, &score_all_arr);
        my_score += cal_score(m, n, -1, 1, enemy_list, my_list, &score_all_arr);
    }
    freeLinkListIterator(it);
    LinkListIterator *it2 = createLinkListIterator(enemy_list);
    while(LinkListIteratorHasNext(it2))
    {
        pos *elem = (pos*)LinkListIteratorNext(it2);
        int m = elem->x;
        int n = elem->y;
        enemy_score += cal_score(m, n, 0, 1, my_list, enemy_list, &score_all_arr_enemy);
        enemy_score += cal_score(m, n, 1, 0, my_list, enemy_list, &score_all_arr_enemy);
        enemy_score += cal_score(m, n, 1, 1, my_list, enemy_list, &score_all_arr_enemy);
        enemy_score += cal_score(m, n, -1, 1, my_list, enemy_list, &score_all_arr_enemy);
    }
    freeLinkListIterator(it2);
    total_score = my_score - enemy_score*ratio*0.1;
    freeLinkList(score_all_arr);
    freeLinkList(score_all_arr_enemy);
    return total_score;
}



double negmax(int isAI, int depth, int alpha, int beta)
{
    if(game_win(list1) || game_win(list2) || depth==0)
    {
        return evaluation(isAI);
    }
    LinkList *blank_list = createLinkList();
    posListDifference(list_all,list3,blank_list);
    order(blank_list);
    LinkListIterator *it = createLinkListIterator(blank_list);
    
    while(LinkListIteratorHasNext(it))
    {
         pos *elem = (pos*) LinkListIteratorNext(it);
         pos *elem_cp = (pos*) malloc(sizeof(pos));
         elem_cp->x = elem->x; elem_cp->y = elem->y;
         if(hasNeighbour(*elem)==0) continue;
         if(isAI)
         {
             LinkListInsertDataAtLast(list1,elem_cp);
         }else{
             LinkListInsertDataAtLast(list2,elem_cp);
         }
         LinkListInsertDataAtLast(list3,elem_cp);
         int is_ai = 0, idx=0;
         if(!isAI) is_ai=1; 
         double value = -negmax(is_ai, depth - 1, -beta, -alpha);
         if(isAI)
         {
             idx = findPosInList(*elem,list1);
             LinkListRemoveDataAt(list1,idx);
       
         }else{
             idx = findPosInList(*elem,list2);
             LinkListRemoveDataAt(list2,idx);
         }
         idx = findPosInList(*elem,list3);
         LinkListRemoveDataAt(list3,idx);
         if(value > alpha)
         {
             if(depth==DEPTH)
             {
                 next_point.x = elem_cp->x;
                 next_point.y = elem_cp->y;
             }
             // alpha beta prunning point 
             if(value>=beta)
             {
                 return (double)beta;
             }
             alpha = value;
         }
    }
    
    freeLinkListIterator(it);
    freeLinkList(blank_list);
    return alpha;
}

pos AI_Step()
{
    double ans3 = negmax(1,DEPTH,-99999999,99999999);
    pos ret = {.x=next_point.x,.y=next_point.y};
    return ret;
}


static void garbage_collection()
{
    freeLinkList(list1);
    freeLinkList(list2);
    LinkListIterator *it = createLinkListIterator(list3);
    while(LinkListIteratorHasNext(it))
    {
        pos *elem = (pos*)LinkListIteratorNext(it);
        free(elem);
    }
    freeLinkListIterator(it);
    freeLinkList(list3);
    LinkListIterator *it2 = createLinkListIterator(list_all);
    while(LinkListIteratorHasNext(it2))
    {
        pos *elem = (pos*)LinkListIteratorNext(it2);
        free(elem);
    }
    freeLinkListIterator(it2);
    freeLinkList(list_all);
}

void test_GoBangAI()
{
    LinkList *score_all_arr = createLinkList();
    LinkList *my_list = createLinkList();
    LinkList *enemy_list = createLinkList();
    //(5.0, 8.0, [(5.0, 9.0), (3, 8), (3, 9)], [(4.0, 8.0), (5.0, 8.0), (4, 9)], [(50, ((4.0, 6.0), (4.0, 7.0), 
    //(4.0, 8.0), (4.0, 9.0), (4.0, 10.0)), (0, 1))], -1, 1)
    scoreshape *max_score_shape = (scoreshape*)malloc(sizeof(scoreshape));
    max_score_shape->pos_arr_size = 5;
    max_score_shape->score_val = 50;
    int i,j;
    pos z[5] = {{4,6},{4,7},{4,8},{4,9},{4,10}};
    for(i=0;i<max_score_shape->pos_arr_size;++i)
    {
        max_score_shape->pos_arr[i] = z[i];
    }
    pos direc = {.x=0,.y=1};
    max_score_shape->direct = direc;
    LinkListInsertDataAtLast(score_all_arr,max_score_shape);
    //my_list = [(4.0, 8.0), (5.0, 8.0), (4, 9)]
    pos mylistArr[3] = {{4,8},{5,8},{4,9}};
    pos enemylistArr[3] = {{5,9},{3,9},{5,10}};
    for(i=0;i<3;++i)
    {
        LinkListInsertDataAtLast(my_list,&mylistArr[i]);
        LinkListInsertDataAtLast(enemy_list,&enemylistArr[i]);
    }
    
    int ans = cal_score(4,8,1,0,enemy_list,my_list,&score_all_arr);
    printf("ans=%d\n",ans);//ans=150
    
    //test global_shape_score
    for(i=0;i<15;i++)
    {
        scorest tmp = global_shape_score[i];
        for(j=0;j<tmp.scorest_size;j++)
        {
            printf("%d ",tmp.scorest_arr[j]);
        }
        printf("\n");
    }
    
    freeLinkList(score_all_arr);
    // test function order
    list3 = createLinkList();
    LinkList *blank_list = createLinkList();
    pos list3Arr[] = {{3.0, 6.0}, {4.0, 7.0}, {4.0, 6.0}, {5.0, 6.0}};
    pos blankListArr[7] = {{6, 9}, {12, 1}, {11, 11}, {7, 12}, {14, 4}, {13, 4}, {7,5}};
    for(i=0;i<4;++i)
    {
        LinkListInsertDataAtLast(list3,&list3Arr[i]);
    }
    for(i=0;i<7;++i)
    {
        LinkListInsertDataAtLast(blank_list,&blankListArr[i]);
    }
    order(blank_list);
    LinkListIterator *it_blank = createLinkListIterator(blank_list);
    while(LinkListIteratorHasNext(it_blank))
    {
        pos *elem = (pos*)LinkListIteratorNext(it_blank);
        printf("(%d,%d)\n",elem->x,elem->y);
    }
    freeLinkListIterator(it_blank);
    freeLinkList(blank_list);
    
    // test function list difference
    LinkList *blank_list2 = createLinkList();
    posListDifference(list_all,list3,blank_list2);
    printf("list_all.size=%d\n",list_all->count);
    printf("blank_list2.size=%d\n",blank_list2->count);
    freeLinkList(blank_list2);
    
    //test negmax
    pos list1arr[] = {{4,7},{5,6}};
    pos list2arr[] = {{3,6},{4,6}};
    list1 = createLinkList();
    list2 = createLinkList();
    LinkListInsertDataAtLast(list1,&list1arr[0]);
    LinkListInsertDataAtLast(list1,&list1arr[1]);
    LinkListInsertDataAtLast(list2,&list2arr[0]);
    LinkListInsertDataAtLast(list2,&list2arr[1]);
    double ans3 = negmax(1,3,-99999999,99999999);
    printf("%f\n",ans3);
    assert(ans3==960.0);
}

void display_board(char board[][COLUMN+1])
{
    int i,j;
    for(i=0;i<ROW+2;++i)
    {
        for(j=0;j<COLUMN+2;++j)
        {
            if(i==0)
            {
                if(j<10)
                    printf("%d  ",j);
                else
                    printf("%d ",j);
            }
            else if(j==0)
            {
                if(i<10)
                    printf("%d  ",i);
                else
                    printf("%d ",i);
            }else
            {
                printf("%c  ",board[i-1][j-1]);
            }
        }
        printf("\n");
    }
}


void GoBang_Main()
{
    int i,j;
    init_global_shape_score();
    list_all = createLinkList();
    list1 = createLinkList();
    list2 = createLinkList();
    list3 = createLinkList();
    for(i=0;i<ROW+1;++i)
    {
        for(j=0;j<COLUMN+1;++j)
        {
            pos *p = (pos*)malloc(sizeof(pos));
            p->x = i; p->y = j;
            LinkListInsertDataAtLast(list_all, p);
        }
    }

    // draw the board
    char chessboard[ROW+1][COLUMN+1];
    for(i=0;i<ROW+1;++i)
    {
        for(j=0;j<COLUMN+1;++j)
        {
            chessboard[i][j]='.';
        }
    }
    display_board(chessboard);
    int g=0,change=0;
    
    while(g==0)
    {
        if(change%2==1)
        {
            pos ret = AI_Step();
            if(isPosInList(ret,list3))
            {
                printf("Illegal Position for AI\n");
                g=1;
            }
            pos *ret_cp = (pos*)malloc(sizeof(pos));
            ret_cp->x = ret.x; ret_cp->y = ret.y;
            LinkListInsertDataAtLast(list1,ret_cp);
            LinkListInsertDataAtLast(list3,ret_cp);
            chessboard[ret.x][ret.y]='X';
            display_board(chessboard);
            if(game_win(list1))
            {
                printf("AI win\n");
                g=1;
            }
            
            change++;
        }else
        {
            int a2,b2;
            printf("Your Turn: Input the position you want to drop (X,Y)\n");
            scanf("%d,%d",&a2,&b2);
            pos ret={a2-1,b2-1};
            if(isPosInList(ret,list3))
            {
                printf("The drop position is already used, illegal.\n");
                continue;
            }
            if(ret.x<0 || ret.x>ROW || ret.y<0 || ret.y>COLUMN)
            {
                printf("The drop position is Boundary Exceeded, illegal.\n");
                continue;
            }
            pos *ret_cp = (pos*)malloc(sizeof(pos));
            ret_cp->x = a2-1; ret_cp->y=b2-1;
            LinkListInsertDataAtLast(list2,ret_cp);
            LinkListInsertDataAtLast(list3,ret_cp);
            chessboard[ret.x][ret.y]='O';
            display_board(chessboard);
            if(game_win(list2))
            {
                printf("Player win\n");
                g=1;
            }
            change++;
        }
    }
    garbage_collection();
    //test_GoBangAI();
}