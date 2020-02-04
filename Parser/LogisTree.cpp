//########################################################
//##                                                    ##
//##        Author:    xfu                              ##
//##        E-Mail:    tech@zhongwenshu.de              ##
//##                                                    ##
//########################################################

//物流表达式
//%铁路(中通6666 + 圆通YT(8888 + 5641)) + %空运(JD0001-1-1)

#include "stdafx.h"
#include "LogisTree.h"
#include "..\Tool\Operation.h"


using namespace std;
using namespace XFU;


wstring LogisTreeNode::ToString() const
{
   wstring res = L"";

   if (HasChild())
   {
      FOR_EACH(GetChildren(),it,i)
      {
         res += GetChild(i)->ToString();
      }
   }

   return res;
}

wstring LogisTreeNodeExp::ToString() const
{
   return GetChild(0)->ToString() + GetChild(1)->ToString();
}

wstring LogisTreeNodeExp1::ToString() const
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

wstring LogisTreeNodeKeyexp::ToString() const
{
   return GetKeyword() + L"(" + GetChild(0)->ToString() + L")";
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
