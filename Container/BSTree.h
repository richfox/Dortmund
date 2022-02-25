#pragma once

#include <vector>


template<typename T>
struct BSTree
{
   BSTree(T element)
      :_element(element),
      _lson(nullptr),
      _rson(nullptr),
      _parent(nullptr)
   {}

   BSTree(const BSTree<T>& tree)
   {
      Destroy();
      _element = tree._element;
      _lson = tree._lson;
      _rson = tree._rson;
      _parent = tree._parent;
   }

   ~BSTree()
   {
      Destroy();
   }

   void Destroy()
   {
      if (_lson)
         delete _lson;
      if (_rson)
         delete _rson;
   }

   int CountOfVetex() const
   {
      int count = 1;
      if (_lson)
         count += _lson->CountOfVetex();
      if (_rson)
         count += _rson->CountOfVetex();
      return count;
   }

   std::vector<T> InOrder() const
   {
      std::vector<T> res;
      res.reserve(CountOfVetex());

      if (_lson)
      {
         std::vector<T> lres = _lson->InOrder();
         res.insert(res.end(),lres.begin(),lres.end());
      }
      res.push_back(_element);
      if (_rson)
      {
         std::vector<T> rres = _rson->InOrder();
         res.insert(res.end(),rres.begin(),rres.end());
      }

      return res;
   }

   std::vector<T> PreOrder() const
   {
      std::vector<T> res;
      res.reserve(CountOfVetex());

      res.push_back(_element);
      if (_lson)
      {
         std::vector<T> lres = _lson->PreOrder();
         res.insert(res.end(),lres.begin(),lres.end());
      }
      if (_rson)
      {
         std::vector<T> rres = _rson->PreOrder();
         res.insert(res.end(),rres.begin(),rres.end());
      }

      return res;
   }

   std::vector<T> PostOrder() const
   {
      std::vector<T> res;
      res.reserve(CountOfVetex());

      if (_lson)
      {
         std::vector<T> lres = _lson->PostOrder();
         res.insert(res.end(),lres.begin(),lres.end());
      }
      if (_rson)
      {
         std::vector<T> rres = _rson->PostOrder();
         res.insert(res.end(),rres.begin(),rres.end());
      }
      res.push_back(_element);

      return res;
   }

   const BSTree<T>* Search(T k) const 
   {
      if (_element < k)
      {
         if (_rson)
            return _rson->Search(k);
         else
            return nullptr;
      }
      else if (_element > k)
      {
         if (_lson)
            return _lson->Search(k);
         else
            return nullptr;
      }

      return this;
   }

   BSTree<T>* Insert(T k)
   {
      if (_element < k)
      {
         if (_rson)
            return _rson->Insert(k);
         else
         {
            _rson = new BSTree(k);
            _rson->_parent = this;
            return _rson;
         }
      }
      else if (_element > k)
      {
         if (_lson)
            return _lson->Insert(k);
         else
         {
            _lson = new BSTree(k);
            _lson->_parent = this;
            return _lson;
         }
      }

      return this;
   }

   const BSTree<T>* Minimum() const
   {
      while (_lson)
      {
         return _lson->Minimum();
      }

      return this;
   }

   const BSTree<T>* Maximum() const
   {
      while (_rson)
      {
         return _rson->Maximum();
      }

      return this;
   }

   const BSTree<T>* Successor(T k) const
   {
      BSTree<T>* node = const_cast<BSTree<T>*>(Search(k));
      if (node)
      {
         if (node->_rson)
         {
            return node->_rson->Minimum();
         }
         
         BSTree<T>* p = node->_parent;
         while (p && node == p->_rson)
         {
            node = p;
            p = p->_parent;
         }
         return p;
      }

      return nullptr;
   }

   T _element;
   BSTree<T>* _lson;
   BSTree<T>* _rson;
   BSTree<T>* _parent;
};

