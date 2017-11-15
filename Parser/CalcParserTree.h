//########################################################
//##                                                    ##
//##        Author:    xfu                              ##
//##        E-Mail:    tech@zhongwenshu.de              ##
//##                                                    ##
//########################################################

//四则运算语法分析器语法树

#pragma once

#include <memory>
#include <string>
#include <vector>


namespace XFU
{
   enum class CalcTreeNodeType
   {
      Undef = -1,
      Root,
      Expr,
      ExprTail,
      Term,
      TermTail,
      Factor
   };

   //Tree Node Base
   class CalcParserTreeNode
   {
   public:
      CalcParserTreeNode()
         :_type(CalcTreeNodeType::Undef),
         _children()
      {}

      explicit CalcParserTreeNode(const CalcTreeNodeType& type)
         :_type(type),
         _children()
      {}

      CalcParserTreeNode(const CalcTreeNodeType& type,std::shared_ptr<CalcParserTreeNode>& child)
         :_type(type),
         _children(1,child)
      {}

      CalcParserTreeNode(const CalcTreeNodeType& type,const std::vector<std::shared_ptr<CalcParserTreeNode>>& children)
         :_type(type),
         _children(children)
      {}

      virtual ~CalcParserTreeNode()
      {}

      const CalcTreeNodeType& GetType() const
      {
         return _type;
      }

      void AddChild(const std::shared_ptr<CalcParserTreeNode>& child)
      {
         _children.push_back(child);
      }

   private:
      CalcTreeNodeType _type;
      std::vector<std::shared_ptr<CalcParserTreeNode>> _children;
   };




   //Factor ->  (Expr)
   //       |   num
   class CalcParserTreeNodeFactor final : public CalcParserTreeNode
   {
   public:
      CalcParserTreeNodeFactor()
         :CalcParserTreeNode(CalcTreeNodeType::Factor),
         _number()
      {}

      virtual ~CalcParserTreeNodeFactor()
      {}

      void SetNumber(const std::wstring& number)
      {
         _number = number;
      }

   private:
      std::wstring _number;
   };




   //Term -> Factor TermTail
   class CalcParserTreeNodeTerm final : public CalcParserTreeNode
   {
   public:
      CalcParserTreeNodeTerm()
         :CalcParserTreeNode(CalcTreeNodeType::Term)
      {}

      ~CalcParserTreeNodeTerm()
      {}
   };




   //TermTail -> * Factor TermTail
   //         |  / Factor TermTail
   //         |  null
   class CalcParserTreeNodeTermTail final : public CalcParserTreeNode
   {
   public:
      CalcParserTreeNodeTermTail()
         :CalcParserTreeNode(CalcTreeNodeType::TermTail),
         _op(L"")
      {}

      ~CalcParserTreeNodeTermTail()
      {}

      void SetOp(const std::wstring& op)
      {
         _op = op;
      }

   private:
      std::wstring _op;
   };


   //Expr -> Term ExprTail
   class CalcParserTreeNodeExpr final : public CalcParserTreeNode
   {
   public:
      CalcParserTreeNodeExpr()
         :CalcParserTreeNode(CalcTreeNodeType::Expr)
      {}

      ~CalcParserTreeNodeExpr()
      {}
   };


   //ExprTail -> + Term ExprTail
   //         |  - Term ExprTail
   //         |  null
   class CalcParserTreeNodeExprTail final : public CalcParserTreeNode
   {
   public:
      CalcParserTreeNodeExprTail()
         :CalcParserTreeNode(CalcTreeNodeType::ExprTail),
         _op(L"")
      {}

      void SetOp(const std::wstring& op)
      {
         _op = op;
      }

   private:
      std::wstring _op;
   };

}