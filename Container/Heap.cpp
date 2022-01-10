#include "stdafx.h"
#include "Heap.h"
#include <iostream>

using namespace std;


void Heap::Sort(int index)
{
   if (index > 1)
   {
      int parentIndex = Parent(index);
      if (_heapAsArray[index] < _heapAsArray[parentIndex])
      {
         Swap(&_heapAsArray[index],&_heapAsArray[parentIndex]);
         Sort(parentIndex);
      }
   }
}

void Heap::Insert(int elem)
{
   if (!IsFull())
   {
      _heapAsArray[++_countNodes] = elem;
      Sort(_countNodes);
   }
}

void Heap::Heapify(int index)
{
   int leftIndex = Left(index);
   int rightIndex = Right(index);
   if (leftIndex<=_countNodes && rightIndex>_countNodes)
   {
      //there is no child at the right side
      if (_heapAsArray[leftIndex] < _heapAsArray[index])
      {
         Swap(&_heapAsArray[index],&_heapAsArray[leftIndex]);
      }
   }
   else if (rightIndex <= _countNodes)
   {
      //exist already children at the left and right side
      int selIndex = (_heapAsArray[leftIndex] < _heapAsArray[rightIndex]) ? leftIndex : rightIndex;
      if (_heapAsArray[selIndex] < _heapAsArray[index])
      {
         Swap(&_heapAsArray[index],&_heapAsArray[selIndex]);
         Heapify(selIndex);
      }
   }
}

//int Heap::Remove()
//{
//   int root = _heapAsArray[1];
//   _heapAsArray[1] = _heapAsArray[_countNodes--];
//   Heapify(1);
//   
//   return root;
//}

int Heap::Remove(int index)
{
   int elem = _heapAsArray[index];
   _heapAsArray[index] = _heapAsArray[_countNodes--];
   int parentIndex = Parent(index);
   if (index==1 || _heapAsArray[index]>=_heapAsArray[parentIndex])
   {
      Heapify(index);
   }
   else
   {
      Sort(index);
   }

   return elem;
}

void Heap::Decrease(int index,int elem)
{
   if (elem < _heapAsArray[index])
   {
      _heapAsArray[index] = elem;
      Sort(index);
   }
}

void Heap::Print()
{
   int n = 1;
   for (int i=1; i<=_countNodes; i++)
   {
      cout << _heapAsArray[i] << "#";
      int x = int(pow(2,n)) - 1; //index of the last node of a level
      if (i%x == 0)
      {
         cout << endl;
         n++; //a new level start
      }
   }
   cout << "\n____________________________" << endl;
}