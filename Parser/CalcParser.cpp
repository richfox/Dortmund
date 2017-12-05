//########################################################
//##                                                    ##
//##        Author:    xfu                              ##
//##        E-Mail:    tech@zhongwenshu.de              ##
//##                                                    ##
//########################################################

// Parser.cpp


#include "stdafx.h"
#include "CalcParser.h"
#include <regex>
#include <memory>
#include "CalcParserTree.h"


using namespace std;
using namespace XFU;



std::shared_ptr<CalcParserTreeNode> Parser::Run()
{
   std::shared_ptr<CalcParserTreeNode> tree(new CalcParserTreeNode(CalcTreeNodeType::Root));
   _currentnode = tree.get();

   _tokenit = _tokens.begin();

   if (Expr())
   {
      _success = true;
   }

   return tree;
}



bool Parser::Number()
{
   wregex rx(L"^[0-9]+$");
   return regex_search(*_tokenit,rx);
}

bool Parser::NextToken()
{
   if (_tokenit != _tokens.end()-1)
   {
      _tokenit++;
      return true;
   }
   
   return false;
}



//Expr -> Term ExprTail
bool Parser::Expr()
{
   std::shared_ptr<CalcParserTreeNodeExpr> node(new CalcParserTreeNodeExpr);
   _currentnode->AddChild(node);
   _currentnode = node.get();

   if (Term())
   {
      _currentnode = node.get(); //Factor过程中current node可能被改变了，我们重置一下

      return ExprTail();
   }

   return false;
}

//ExprTail -> + Term ExprTail
//         |  - Term ExprTail
//         |  null
bool Parser::ExprTail()
{
   std::shared_ptr<CalcParserTreeNodeExprTail> node(new CalcParserTreeNodeExprTail);
   _currentnode->AddChild(node);
   _currentnode = node.get();

   if (*_tokenit==L"+" || *_tokenit==L"-")
   {
      node->SetOp(*_tokenit);

      if (NextToken()) //Next token always after matching
      {
         if (Term())
         {
            _currentnode = node.get(); //Factor过程中current node可能被改变了，我们重置一下

            return ExprTail();
         }
         else
         {
            return false;
         }
      }
      else
      {
         return false;
      }
   }

   return true;
}

//Term -> Factor TermTail
bool Parser::Term()
{
   std::shared_ptr<CalcParserTreeNodeTerm> node(new CalcParserTreeNodeTerm);
   _currentnode->AddChild(node);
   _currentnode = node.get();

   if (Factor())
   {
      _currentnode = node.get(); //Factor过程中current node可能被改变了，我们重置一下

      return TermTail();
   }

   return false;
}

//TermTail -> * Factor TermTail
//         |  / Factor TermTail
//         |  null
bool Parser::TermTail()
{
   std::shared_ptr<CalcParserTreeNodeTermTail> node(new CalcParserTreeNodeTermTail);
   _currentnode->AddChild(node);
   _currentnode = node.get();

   if (*_tokenit==L"*" || *_tokenit==L"/")
   {
      node->SetOp(*_tokenit);

      if (NextToken())
      {
         if (Factor())
         {
            _currentnode = node.get(); //Factor过程中current node可能被改变了，我们重置一下

            return TermTail();
         }
         else
         {
            return false;
         }
      }
      else
      {
         return false;
      }
   }

   return true;
}

//Factor -> (Expr)
//       |  num
bool Parser::Factor()
{
   std::shared_ptr<CalcParserTreeNodeFactor> node(new CalcParserTreeNodeFactor);
   _currentnode->AddChild(node);
   _currentnode = node.get();

   if (*_tokenit == L"(")
   {
      if (NextToken())
      {
         if (Expr())
         {
            if (*_tokenit == L")")
            {
               NextToken();
               return true;
            }
         }
      }
   }
   else if (Number())
   {
      node->SetNumber(*_tokenit);

      NextToken();
      return true;
   }

   return false;
}



bool XFU::test_parser(const std::vector<std::wstring>& tokens)
{
   std::unique_ptr<Parser> parser(new Parser(tokens));
   parser->Run();

   return parser->IsSuccess();
}

std::shared_ptr<CalcParserTreeNode> XFU::run_parser(const std::vector<std::wstring>& tokens)
{
   std::unique_ptr<Parser> parser(new Parser(tokens));
   return parser->Run();
}