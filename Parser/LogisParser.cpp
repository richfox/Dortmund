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

//Exp -> keyword (Exp) Exp'
//     | Text Exp'
bool LogisParser::Exp()
{
   shared_ptr<LogisTreeNodeExp> node(new LogisTreeNodeExp);
   _currentnode->AddChild(node);
   _currentnode = node.get();


   return false;
}

//Exp' -> + Exp''
//      | null
bool LogisParser::Exp1()
{
   shared_ptr<LogisTreeNodeExp1> node(new LogisTreeNodeExp1);
   _currentnode->AddChild(node);
   _currentnode = node.get();

   return false;
}

//Exp'' -> keyword (Exp)
//       | Text
bool LogisParser::Exp2()
{
   shared_ptr<LogisTreeNodeExp2> node(new LogisTreeNodeExp2);
   _currentnode->AddChild(node);
   _currentnode = node.get();

   return false;
}

//Text -> Header Factor
//      | Factor
bool LogisParser::Text()
{
   shared_ptr<LogisTreeNodeText> node(new LogisTreeNodeText);
   _currentnode->AddChild(node);
   _currentnode = node.get();

   return false;
}

//Factor -> ( sn Tail )
//        | sn
bool LogisParser::Factor()
{
   shared_ptr<LogisTreeNodeFactor> node(new LogisTreeNodeFactor);
   _currentnode->AddChild(node);
   _currentnode = node.get();

   return false;
}

//Tail -> + sn Tail
//      | null
bool LogisParser::Tail()
{
   shared_ptr<LogisTreeNodeTail> node(new LogisTreeNodeTail);
   _currentnode->AddChild(node);
   _currentnode = node.get();

   return false;
}