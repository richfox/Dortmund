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
   if (GetKeyword().empty())
   {
      return GetText() + GetChild(0)->ToString();
   }
   else
   {
      return GetKeyword() + L"(" + GetChild(0)->ToString() + L")" + GetChild(1)->ToString();
   }
}

wstring LogisTreeNodeExp1::ToString() const
{
   if (HasChild())
   {
      return wstring(L"+") + GetChild(0)->ToString();
   }
   else
   {
      return L"";
   }
}

wstring LogisTreeNodeExp2::ToString() const
{
   if (GetKeyword().empty())
   {
      return GetText();
   }
   else
   {
      return GetKeyword() + L"(" + GetChild(0)->ToString() + L")";
   }
}

wstring LogisTreeNodeText::ToString() const
{
   if (GetHeader().empty())
   {
      return GetChild(0)->ToString();
   }
   else
   {
      return GetHeader() + GetChild(0)->ToString();
   }
}

wstring LogisTreeNodeFactor::ToString() const
{
   if (HasLbracket())
   {
      return wstring(L"(") + GetChild(0)->ToString() + GetChild(1)->ToString() + L")";
   }
   else
   {
      return GetChild(0)->ToString(); 
   }
}

wstring LogisTreeNodeTail::ToString() const
{
   if (HasChild())
   {
      return wstring(L"+") + GetChild(0)->ToString() + GetChild(1)->ToString();
   }
   else
   {
      return L"";
   }
}