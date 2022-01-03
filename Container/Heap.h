#pragma once


#include <math.h>
#include <limits.h>


const int maxNodes = 70;
const int undef = INT_MIN;


class Heap
{
public:
   void Init()
   {
      _countNodes = 0;
   }

   bool IsEmpty()
   {
      return _countNodes==0 ? true : false;
   }

   bool IsFull()
   {
      return _countNodes>=maxNodes+1 ? true : false;
   }

   int Head()
   {
      return IsEmpty() ? undef : _heapAsArray[1];
   }

   void Insert(int elem);

private:
   int Parent(int index)
   {
      return index / 2;
   }

   int Left(int index)
   {
      return index * 2;
   }

   int Right(int index)
   {
      return index * 2 + 1;
   }

   void Swap(int* a,int* b)
   {
      int temp = *a;
      *a = *b;
      *b = temp;
   }

   void Sort(int index);
   void Heapify(int index);

private:
   int _heapAsArray[maxNodes + 1]; //start with index 1, index 0 is not used!
   int _countNodes;
};