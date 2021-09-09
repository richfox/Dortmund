#pragma once


template<typename T>
struct BSTree
{
   BSTree(T element)
      :_element(element),
      lson(nullptr),
      rson(nullptr)
   {}

   ~BSTree()
   {
      delete lson;
      delete rson;
   }

   void InOrder()
   {
      if (lson)
         lson->InOrder();

      std::cout << _element << " ";

      if (rson)
         rson->InOrder();
   }

   T _element;
   BSTree<T>* lson;
   BSTree<T>* rson;
};

template<typename T>
bool search(BSTree<T>* bst, T k)
{
   if (bst == nullptr)
   {
      return false;
   }
   else
   {
      if (bst->_element < k)
      {
         return search(bst->rson,k);
      }
      else if (bst->_element > k)
      {
         return search(bst->lson,k);
      }

      return true;
   }
}

template<typename T>
BSTree<T>* insert(BSTree<T>* bst,int k)
{
   if (bst == nullptr)
   {
      bst = new BSTree<T>(k);
   }
   else
   {
      if (bst->_element < k)
      {
         bst->rson = insert(bst->rson,k);
      }
      else if (bst->_element > k)
      {
         bst->lson = insert(bst->lson,k);
      }
   }

   return bst;
}