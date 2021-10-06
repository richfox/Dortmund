#pragma once

#include <iostream>

//n皇后问题

namespace xfu
{
   int q[20] = {};   //各皇后所在列号,最多放皇后20个
   int count = 0;    //统计解个数


   //输出一个解
   void print_queen(int n)
   {
     count++;
     printf("the %dth solution: ",count);
     for(int row=0; row<n; row++)
        printf("(%d,%d)",row+1,q[row]+1);
     printf("\n");
     for(int row=0; row<n; row++)
     {               
         for(int col=0; col<n; col++)
         {
            if(q[row] != col)
               printf("x");
            else
               printf("Q");
         }
         printf("\n");
     }
   }

   //检验某行某列上是否可以摆放皇后
   int find_queen(int row,int col) 
   {
     int j = 0;
     while (j < row)  //j=0~row-1是已经放置了皇后的行
     {
         //第j行的皇后是否在k列或(j,q[j])与(row,col)是否在斜线上
         if(q[j]==col || abs(j-row)==abs(q[j]-col))
            return 0;
         j++;
     }
     return 1;
   }

   //放置皇后到棋盘上
   void place_queen(int row,int n) 
   {
     if(row > n-1)
         print_queen(n);
     else
     {
         for(int col=0; col<n; col++)   //试探行的每一列
         {
            if(find_queen(row,col))
            {
               q[row] = col;
               place_queen(row+1,n);  //递归总是在成功完成了上次的任务的时候才做下一个任务
            }
         }
     }
   }
};
