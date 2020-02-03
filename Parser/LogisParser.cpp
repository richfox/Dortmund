//########################################################
//##                                                    ##
//##        Author:    xfu                              ##
//##        E-Mail:    tech@zhongwenshu.de              ##
//##                                                    ##
//########################################################

//物流表达式
//%铁路(中通6666 + 圆通YT(8888 + 5641)) + %空运(JD0001-1-1)

#include "stdafx.h"
#include "LogisParser.h"
#include <regex>
#include <memory>
#include "LogisTree.h"


using namespace std;
using namespace XFU;




shared_ptr<LogisTreeNode> LogisParser::Run()
{
   shared_ptr<LogisTreeNode> tree(new LogisTreeNode(LogisNodeType::Root));
   _currentnode = tree.get();

   _tokenit = _tokens.begin();

   if (Exp())
   {
      _success = true;
   }

   return tree;
}

bool LogisParser::NextToken()
{
   if (_tokenit != _tokens.end()-1)
   {
      _tokenit++;
      return true;
   }
   
   return false;
}

bool LogisParser::Keyword()
{
   wregex pattern(L"^%[a-zA-Z0-9-_\u4e00-\u9fa5]+$"); //以%开头，至少一个数字、字母、减号、下划线、汉字
   return regex_search(*_tokenit,pattern);
}

bool LogisParser::Header()
{
   wregex pattern(L"^[a-zA-Z0-9-_\u4e00-\u9fa5]+$"); //至少一个数字、字母、减号、下划线、汉字
   return regex_search(*_tokenit,pattern);
}

bool LogisParser::Sn()
{
   wregex pattern(L"^[a-zA-Z0-9-]+$"); //至少一个数字、字母、减号
   return regex_search(*_tokenit,pattern);
}

//Exp -> keyword (Exp) Exp'
//     | Text Exp'
bool LogisParser::Exp()
{
   shared_ptr<LogisTreeNodeExp> node(new LogisTreeNodeExp);
   _currentnode->AddChild(node);
   _currentnode = node.get();

   if (Keyword())
   {
      node->SetKeyword(*_tokenit);

      if (NextToken())
      {
         if (*_tokenit == L"(")
         {
            if (Exp())
            {
               if (*_tokenit == L")")
               {
                  _currentnode = node.get();
                  return Exp2();
               }
            }
         }
      }
   }
   else if (Text())
   {
      _currentnode = node.get();
      return Exp2();
   }

   return false;
}

//Exp' -> + Exp''
//      | null
bool LogisParser::Exp1()
{
   shared_ptr<LogisTreeNodeExp1> node(new LogisTreeNodeExp1);
   _currentnode->AddChild(node);
   _currentnode = node.get();

   if (*_tokenit == L"+")
   {
      node->SetOp(*_tokenit);

      if (NextToken())
      {
         return Exp2();
      }
   }
   else
   {
      return true;
   }

   return false;
}

//Exp'' -> keyword (Exp)
//       | Text
bool LogisParser::Exp2()
{
   shared_ptr<LogisTreeNodeExp2> node(new LogisTreeNodeExp2);
   _currentnode->AddChild(node);
   _currentnode = node.get();

   if (Keyword())
   {
      node->SetKeyword(*_tokenit);

      if (NextToken())
      {
         if (*_tokenit == L"(")
         {
            if (Exp())
            {
               if (*_tokenit == L")")
               {
                  return true;
               }
            }
         }
      }
   }
   else if (Text())
   {
      return true;
   }

   return false;
}

//Text -> header Factor
//      | Factor
bool LogisParser::Text()
{
   shared_ptr<LogisTreeNodeText> node(new LogisTreeNodeText);
   _currentnode->AddChild(node);
   _currentnode = node.get();

   if (Header())
   {
      node->SetHeader(*_tokenit);

      return Factor();
   }
   else if (Factor())
   {
      return true;
   }

   return false;
}

//Factor -> ( sn Tail )
//        | sn
bool LogisParser::Factor()
{
   shared_ptr<LogisTreeNodeFactor> node(new LogisTreeNodeFactor);
   _currentnode->AddChild(node);
   _currentnode = node.get();

   if (*_tokenit == L"(")
   {
      node->SetLbracket();
      if (NextToken())
      {
         if (Sn())
         {
            node->SetSn(*_tokenit);

            if (Tail())
            {
               if (*_tokenit == L")")
               {
                  NextToken();
                  return true;
               }
            }
         }
      }
   }
   else if (Sn())
   {
      node->SetSn(*_tokenit);

      NextToken();
      return true;
   }

   return false;
}

//Tail -> + sn Tail
//      | null
bool LogisParser::Tail()
{
   shared_ptr<LogisTreeNodeTail> node(new LogisTreeNodeTail);
   _currentnode->AddChild(node);
   _currentnode = node.get();

   if (*_tokenit == L"+")
   {
      if (NextToken())
      {
         if (Sn())
         {
            node->SetSn(*_tokenit);

            return Tail();
         }
      }
   }
   else
   {
      return true;
   }

   return false;
}


bool XFU::test_logis_parser(const std::vector<std::wstring>& tokens)
{
   std::unique_ptr<LogisParser> parser(new LogisParser(tokens));
   parser->Run();

   return parser->IsSuccess();
}

std::shared_ptr<LogisTreeNode> XFU::run_logis_parser(const std::vector<std::wstring>& tokens)
{
   std::unique_ptr<LogisParser> parser(new LogisParser(tokens));
   return parser->Run();
}