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
      Expr,
      ExprTail,
      Term,
      TermTail,
      Factor,
      NumLeaf
   };

   //Tree Node Base
   class CalcParserTreeNode
   {
   public:
      CalcParserTreeNode()
         :_type(CalcTreeNodeType::Undef)
      {}

      explicit CalcParserTreeNode(const CalcTreeNodeType& type)
         :_type(type)
      {}

      virtual ~CalcParserTreeNode()
      {}

      const CalcTreeNodeType& GetType() const
      {
         return _type;
      }

      void SetType(const CalcTreeNodeType& type)
      {
         _type = type;
      }

   private:
      CalcTreeNodeType _type;
   };

   typedef std::shared_ptr<CalcParserTreeNode> SharedNode;
   typedef std::vector<SharedNode> SharedNodes;


   //Factor Base
   class CalcParserTreeNodeFactor : public CalcParserTreeNode
   {
   public:
      CalcParserTreeNodeFactor()
         :CalcParserTreeNode(CalcTreeNodeType::Factor)
      {}

      virtual ~CalcParserTreeNodeFactor()
      {}
   };

   typedef std::shared_ptr<CalcParserTreeNodeFactor> SharedFactor;

   //Factor -> num
   class CalcParserTreeNodeNum final : public CalcParserTreeNodeFactor
   {
   public:
      CalcParserTreeNodeNum(const std::wstring& number)
         :CalcParserTreeNodeFactor()
      {
         SetType(CalcTreeNodeType::NumLeaf);
      }

      ~CalcParserTreeNodeNum()
      {}

   private:
      std::wstring _number;
   };

   //Factor -> (Expr)
   class CalcParserTreeNodeExpr;
   typedef std::shared_ptr<CalcParserTreeNodeExpr> SharedExpr;
   class CalcParserTreeNodeOpExpr final : public CalcParserTreeNodeFactor
   {
   public:
      CalcParserTreeNodeOpExpr(const SharedExpr& expr)
         :CalcParserTreeNodeFactor(),
         _expr(expr)
      {}

      ~CalcParserTreeNodeOpExpr()
      {}

   private:
      SharedExpr _expr;
   };

   

   //Term -> Factor TermTail
   class CalcParserTreeNodeTermTail;
   typedef std::shared_ptr<CalcParserTreeNodeTermTail> SharedTermTail;
   class CalcParserTreeNodeTerm final : public CalcParserTreeNode
   {
   public:
      CalcParserTreeNodeTerm(const SharedFactor& factor,const SharedTermTail& termtail)
         :CalcParserTreeNode(CalcTreeNodeType::TermTail),
         _factor(factor),
         _termtail(termtail)
      {}

      ~CalcParserTreeNodeTerm()
      {}

   private:
      SharedFactor _factor;
      SharedTermTail _termtail;
   };

   typedef std::shared_ptr<CalcParserTreeNodeTerm> SharedTerm;


   //TermTail -> * Factor TermTail
   //         |  / Factor TermTail
   //         |  null
   class CalcParserTreeNodeTermTail final : public CalcParserTreeNode
   {
   public:
      CalcParserTreeNodeTermTail()
         :CalcParserTreeNode(CalcTreeNodeType::TermTail),
         _op(L""),
         _factor(),
         _termtail()
      {}

      CalcParserTreeNodeTermTail(const std::wstring& op,const SharedFactor& factor,const SharedTermTail& termtail)
         :CalcParserTreeNode(CalcTreeNodeType::TermTail),
         _op(op),
         _factor(factor),
         _termtail(termtail)
      {}

   private:
      std::wstring _op;
      SharedFactor _factor;
      SharedTermTail _termtail;
   };


   //Expr -> Term ExprTail
   class CalcParserTreeNodeExprTail;
   typedef std::shared_ptr<CalcParserTreeNodeExprTail> SharedExprTail;
   class CalcParserTreeNodeExpr final : public CalcParserTreeNode
   {
   public:
      CalcParserTreeNodeExpr(const SharedTerm& term,const SharedExprTail& exprtail)
         :CalcParserTreeNode(CalcTreeNodeType::Expr),
         _term(term),
         _exprtail(exprtail)
      {}

      ~CalcParserTreeNodeExpr()
      {}

   private:
      SharedTerm _term;
      SharedExprTail _exprtail;
   };


   //ExprTail -> + Term ExprTail
   //         |  - Term ExprTail
   //         |  null
   class CalcParserTreeNodeExprTail final : public CalcParserTreeNode
   {
   public:
      CalcParserTreeNodeExprTail()
         :CalcParserTreeNode(CalcTreeNodeType::ExprTail),
         _op(L""),
         _term(),
         _exprtail()
      {}

      CalcParserTreeNodeExprTail(const std::wstring& op,const SharedTerm& term,const SharedExprTail& exprtail)
         :CalcParserTreeNode(CalcTreeNodeType::ExprTail),
         _op(op),
         _term(term),
         _exprtail(exprtail)
      {}

   private:
      std::wstring _op;
      SharedTerm _term;
      SharedExprTail _exprtail;
   };


   ///////////////////////////////
   class CalcParserTree final
   {
   public:
      CalcParserTree()
         :_children()
      {}

      explicit CalcParserTree(const SharedNodes& children)
         :_children(children)
      {}

      const SharedNodes& GetChildren() const
      {
         return _children;
      }

   private:
      SharedNodes _children;
   };

}