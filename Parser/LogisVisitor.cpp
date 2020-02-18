//########################################################
//##                                                    ##
//##        Author:    xfu                              ##
//##        E-Mail:    tech@zhongwenshu.de              ##
//##                                                    ##
//########################################################

#include "stdafx.h"
#include <regex>
#include "LogisVisitor.h"


using namespace std;
using namespace logis;


void LogisTreeToString::VisitNode(const LogisTreeNode* node)
{
   _oss << node->ToString();
}

void LogisTreeToString::VisitExp(const LogisTreeNodeExp* exp)
{
   _oss << exp->ToString();
}

void LogisTreeToString::VisitKeyExp(const LogisTreeNodeKeyExp* kexp)
{
   _oss << kexp->ToString();
}

void LogisTreeToString::VisitPrimeExp(const LogisTreeNodePrimeExp* pexp)
{
   _oss << pexp->ToString();
}

void LogisTreeToString::VisitText(const LogisTreeNodeText* text)
{
   _oss << text->ToString();
}


wstring logis::run_logis_visitor(const shared_ptr<LogisTreeNode>& tree)
{
   unique_ptr<LogisTreeToString> builder(new LogisTreeToString);
   builder->VisitNode(tree.get());

   return builder->GetString();
}


void LogisTreeSearch::VisitNode(const LogisTreeNode* node)
{
   if (node->HasChild())
   {
      int i = 0;
      for (auto it=node->GetChildren().begin(); it!=node->GetChildren().end(); it++,i++)
      {
         if (_found)
            break;

         VisitNode(node->GetChild(i).get());
      }
   }
}

void LogisTreeSearch::VisitExp(const LogisTreeNodeExp* exp)
{
   VisitNode(exp->GetChild(0).get());

   if (!_found)
   {
      VisitNode(exp->GetChild(1).get());
   }
}

void LogisTreeSearch::VisitKeyExp(const LogisTreeNodeKeyExp* kexp)
{
   VisitNode(kexp->GetChild(0).get());
}

void LogisTreeSearch::VisitPrimeExp(const LogisTreeNodePrimeExp* pexp)
{
   VisitNode(pexp->GetChild(0).get());

   if (!_found)
   {
      VisitNode(pexp->GetChild(1).get());
   }
}

void LogisTreeSearch::VisitText(const LogisTreeNodeText* text)
{
   if (text->HasChild())
   {
      VisitNode(text->GetChild(0).get());
   }
   else
   {
      wstring pattern = wstring(L"^.*") + _sn + L".*$";
      _found = regex_search(text->GetSn(),wregex(pattern));
   }
}