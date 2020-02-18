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
   /*if (node->HasChild())
   {
      int i = 0;
      for (auto it=node->GetChildren().begin(); it!=node->GetChildren().end(); it++,i++)
      {
         if (_found)
            break;

         VisitNode(node->GetChild(i).get());
      }
   }*/
}

void LogisTreeSearch::VisitExp(const LogisTreeNodeExp* exp)
{
   if (exp->GetChild(0)->GetType() == LogisNodeType::Kexp)
   {
      VisitKeyExp(static_cast<LogisTreeNodeKeyExp*>(exp->GetChild(0).get()));
   }
   else
   {
      VisitText(static_cast<LogisTreeNodeText*>(exp->GetChild(0).get()));
   }

   if (!_found)
   {
      VisitPrimeExp(static_cast<LogisTreeNodePrimeExp*>(exp->GetChild(1).get()));
   }
}

void LogisTreeSearch::VisitKeyExp(const LogisTreeNodeKeyExp* kexp)
{
   VisitExp(static_cast<LogisTreeNodeExp*>(kexp->GetChild(0).get()));
}

void LogisTreeSearch::VisitPrimeExp(const LogisTreeNodePrimeExp* pexp)
{
   if (!pexp->GetOp().empty())
   {
      if (pexp->GetChild(0)->GetType() == LogisNodeType::Kexp)
      {
         VisitKeyExp(static_cast<LogisTreeNodeKeyExp*>(pexp->GetChild(0).get()));
      }
      else
      {
         VisitText(static_cast<LogisTreeNodeText*>(pexp->GetChild(0).get()));
      }

      if (!_found)
      {
         VisitPrimeExp(static_cast<LogisTreeNodePrimeExp*>(pexp->GetChild(1).get()));
      }
   }
}

void LogisTreeSearch::VisitText(const LogisTreeNodeText* text)
{
   if (text->HasChild())
   {
      VisitExp(static_cast<LogisTreeNodeExp*>(text->GetChild(0).get()));
   }
   else
   {
      wstring pattern = wstring(L"^.*") + _sn + L".*$";
      _found = regex_search(text->GetSn(),wregex(pattern));
   }
}


bool logis::search_sn(const shared_ptr<LogisTreeNode>& tree,const std::wstring& sn)
{
   unique_ptr<LogisTreeSearch> searcher(new LogisTreeSearch(sn));
   searcher->VisitExp(static_cast<LogisTreeNodeExp*>(tree->GetChild(0).get()));

   return searcher->IsFound();
}