//########################################################
//##                                                    ##
//##        Author:    xfu                              ##
//##        E-Mail:    tech@zhongwenshu.de              ##
//##                                                    ##
//########################################################

//物流表达式
//%铁路(中通6666 + 圆通YT(8888 + 5641)) + %空运(JD0001-1-1)

#include "stdafx.h"
#include <algorithm>
#include "LogisTree.h"
#include "LogisVisitor.h"


using namespace std;
using namespace logis;


wstring LogisTreeNode::ToString() const
{
   wstring res = L"";

   if (HasChild())
   {
      int i = 0;
      for (auto it=GetChildren().begin(); it!=GetChildren().end(); it++,i++)
      {
         res += GetChild(i)->ToString();
      }
   }

   return res;
}

void LogisTreeNode::Accept(LogisVisitor* visitor) const
{
   int i = 0;
   for (auto it=GetChildren().begin(); it!=GetChildren().end(); it++,i++)
   {
      GetChild(i).get()->Accept(visitor);
   }

   visitor->VisitNode(this);
}

int LogisTreeNode::height() const
{
   int h = 0;
   
   if (HasChild())
   {
      h = 1;
      auto& it = max_element(GetChildren().begin(),GetChildren().end(),[&](const shared_ptr<LogisTreeNode>& lhs,const auto& rhs)
      {
         return lhs->height() < rhs->height();
      });
      h += (*it)->height();
   }

   return h;
}

int logis::get_tree_height(const std::shared_ptr<LogisTreeNode>& tree)
{
   return tree->height();
}

wstring LogisTreeNodeExp::ToString() const
{
   return GetChild(0)->ToString() + GetChild(1)->ToString();
}

void LogisTreeNodeExp::Accept(LogisVisitor* visitor) const
{
   visitor->VisitExp(this);
}

wstring LogisTreeNodePrimeExp::ToString() const
{
   if (!GetOp().empty())
   {
      return GetOp() + GetChild(0)->ToString() + GetChild(1)->ToString();
   }
   else
   {
      return L"";
   }
}

void LogisTreeNodePrimeExp::Accept(LogisVisitor* visitor) const
{
   visitor->VisitPrimeExp(this);
}

wstring LogisTreeNodeKeyExp::ToString() const
{
   return GetKeyword() + L"(" + GetChild(0)->ToString() + L")";
}

void LogisTreeNodeKeyExp::Accept(LogisVisitor* visitor) const
{
   visitor->VisitKeyExp(this);
}

wstring LogisTreeNodeText::ToString() const
{
   if (HasChild())
   {
      return wstring(L"(") + GetChild(0)->ToString() + wstring(L")");
   }
   else
   {
      return GetSn();
   }
}

void LogisTreeNodeText::Accept(LogisVisitor* visitor) const
{
   visitor->VisitText(this);
}