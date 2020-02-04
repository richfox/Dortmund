﻿//########################################################
//##                                                    ##
//##        Author:    xfu                              ##
//##        E-Mail:    tech@zhongwenshu.de              ##
//##                                                    ##
//########################################################

//物流表达式
//%铁路(中通6666 + 圆通YT(8888 + 5641)) + %空运(JD0001-1-1)


//  (  表达式的根 %铁路(中通6666 + 圆通YT(8888 + 5641)) + %空运(JD0001-1-1) ) 
//               |                                    |             |
//             %铁路                                  +           %空运       
//      /        |         \                                        |
// 中通6666      +    圆通YT(8888 + 5641)                        JD0001-1-1
//                    /            \
//                 圆通YT        8888 + 5641
//                              /     |     \
//                           8888     +     5641


//语法
//Exp -> Keyexp Exp'
//     | Text Exp'
//Exp' -> + Keyexp Exp'
//      | + Text Exp'
//      | null
//Keyexp -> keyword (Exp)
//Text -> (Exp)
//      | sn

#pragma once

#include <string>
#include <vector>
#include <memory>


namespace XFU
{
   enum class LogisNodeType
   {
      Undef = -1,
      Root,
      Exp,
      Exp1,
      Kexp,
      Text
   };

   class LogisTreeNode
   {
   public:
      LogisTreeNode()
         :_type(LogisNodeType::Undef),
         _children()
      {}

      explicit LogisTreeNode(const LogisNodeType type)
         :_type(type),
         _children()
      {}

      LogisTreeNode(const LogisNodeType type,const std::shared_ptr<LogisTreeNode>& child)
         :_type(type),
         _children(1,child)
      {}

      LogisTreeNode(const LogisNodeType type,const std::vector<std::shared_ptr<LogisTreeNode>>& children)
         :_type(type),
         _children(children)
      {}

      virtual ~LogisTreeNode()
      {}

      const LogisNodeType GetType() const
      {
         return _type;
      }

      void AddChild(const std::shared_ptr<LogisTreeNode>& child)
      {
         _children.push_back(child);
      }

      bool HasChild() const
      {
         return !_children.empty();
      }

      const std::shared_ptr<LogisTreeNode>& GetChild(int idx) const
      {
         return _children[idx];
      }

      const std::vector<std::shared_ptr<LogisTreeNode>>& GetChildren() const
      {
         return _children;
      }

      virtual std::wstring ToString() const;

   private:
      LogisNodeType _type;
      std::vector<std::shared_ptr<LogisTreeNode>> _children;
   };


   //Exp -> Keyexp Exp'
   //     | Text Exp'
   class LogisTreeNodeExp final : public LogisTreeNode
   {
   public:
      LogisTreeNodeExp()
         :LogisTreeNode(LogisNodeType::Exp)
      {}

      ~LogisTreeNodeExp()
      {}

      std::wstring ToString() const;
   };


   //Exp' -> + Keyexp Exp'
   //      | + Text Exp'
   //      | null
   class LogisTreeNodeExp1 final : public LogisTreeNode
   {
   public:
      LogisTreeNodeExp1()
         :LogisTreeNode(LogisNodeType::Exp1),
         _op(L"")
      {}

      ~LogisTreeNodeExp1()
      {}

      void SetOp(const std::wstring& op)
      {
         _op = op;
      }

      const std::wstring& GetOp() const
      {
         return _op;
      }

      std::wstring ToString() const;

   private:
      std::wstring _op;
   };


   //Keyexp -> keyword (Exp)
   class LogisTreeNodeKeyexp final : public LogisTreeNode
   {
   public:
      LogisTreeNodeKeyexp()
         :LogisTreeNode(LogisNodeType::Kexp),
         _keyword(L"")
      {}

      ~LogisTreeNodeKeyexp()
      {}

      void SetKeyword(const std::wstring& keyword)
      {
         _keyword = keyword;
      }

      const std::wstring& GetKeyword() const
      {
         return _keyword;
      }

      std::wstring ToString() const;

   private:
      std::wstring _keyword;
   };


   //Text -> (Exp)
   //      | sn
   class LogisTreeNodeText final : public LogisTreeNode
   {
   public:
      LogisTreeNodeText()
         :LogisTreeNode(LogisNodeType::Text),
         _sn(L"")
      {}

      ~LogisTreeNodeText()
      {}

      void SetSn(const std::wstring& sn)
      {
         _sn = sn;
      }

      const std::wstring& GetSn() const
      {
         return _sn;
      }

      std::wstring ToString() const;

   private:
      std::wstring _sn;
   };
}