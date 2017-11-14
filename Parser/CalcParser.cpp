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



SharedNodes Parser::Run()
{
   _tokenit = _tokens.begin();

   if (Expr())
   {
      _success = true;
   }

   return _tree;
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
   if (Term())
   {
      return ExprTail();
   }

   return false;
}

//ExprTail -> + Term ExprTail
//         |  - Term ExprTail
//         |  null
bool Parser::ExprTail()
{
   if (*_tokenit==L"+" || *_tokenit==L"-")
   {
      if (NextToken()) //Next token always after matching
      {
         if (Term())
         {
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
   if (Factor())
   {
      return TermTail();
   }

   return false;
}

//TermTail -> * Factor TermTail
//         |  / Factor TermTail
//         |  null
bool Parser::TermTail()
{
   if (*_tokenit==L"*" || *_tokenit==L"/")
   {
      if (NextToken())
      {
         if (Factor())
         {
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
      NextToken();
      return true;
   }

   return false;
}



bool XFU::run_parser(const std::vector<std::wstring>& tokens)
{
   std::unique_ptr<Parser> parser(new Parser(tokens));
   parser->Run();

   return parser->IsSuccess();
}