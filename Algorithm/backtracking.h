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


   ////////////////////////////////////////////////

   //使用位运算求解, sum用来记录皇后放置成功的不同布局数
   long sum = 0;

   void bqueen(long row, long pie, long na, long n)
   {
      //upperlim用来标记所有行都已经放置好了皇后的状态
      long upperlim = (1<<n) - 1;
      if(row != upperlim)
      {
         //row，pie撇，na捺，分别表示在纵列和两个对角线方向的限制条件下这一行的哪些地方不能放
         //把它们三个并起来，得到该行所有的禁位
         //然后再取反，来求得这一行所有可以放置皇后的位置，对应位1
         //再“与”n位全1的数表示同时不能超过n位有效位置，否则平移后会陷入死循环
         long pos = upperlim & ~(row | pie | na);
         while (pos)    // 0 -- 皇后没有地方可放，回溯
         {
            //-pos相当于not pos + 1，pos and (not pos + 1)其结果是取出最右边为1的bit
            //也就是取得可以放皇后的最右边的列，比如：
            //       pos = 00110100
            //      ~pos = 11001011
            //      -pos = 11001100
            //pos & -pos = 00000100
            long p = pos & -pos;

            //将pos最右边为1的bit清零
            pos -= p;

            //注意递归调用时每个参数都加上了一个禁位，
            //但两个对角线方向的禁位对下一行的影响需要平移一位，撇方向向左，捺方向向右
            bqueen(row + p, (pie + p) << 1, (na + p) >> 1, n);                             
         }
      }
      else
      {
         //row的所有位都为1，即找到了一个成功的布局，回溯
         sum++;
      }
   }

};
