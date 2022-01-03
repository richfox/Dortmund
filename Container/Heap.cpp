#include "stdafx.h"
#include "Heap.h"


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
      int selIndex = (_heapAsArray[leftIndex] < _heapAsArray[rightIndex]) ? _heapAsArray[leftIndex] : _heapAsArray[rightIndex];
      if (_heapAsArray[selIndex] < _heapAsArray[index])
      {
         Swap(&_heapAsArray[index],&_heapAsArray[selIndex]);
         Heapify(selIndex);
      }
   }
}