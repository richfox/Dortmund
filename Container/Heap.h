#pragma once


#include <math.h>
#include <limits.h>


const int maxNodes = 70;
const int undef = INT_MIN;


class __declspec(dllexport) Heap
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
   int Remove(int index);
   void Print();
   void Decrease(int index,int elem);

private:
   __forceinline int Parent(int index)
   {
      return index / 2;
   }

   __forceinline int Left(int index)
   {
      return index * 2;
   }

   __forceinline int Right(int index)
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