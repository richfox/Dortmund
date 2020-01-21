//########################################################
//##                                                    ##
//##        Author:    xfu                              ##
//##        E-Mail:    tech@zhongwenshu.de              ##
//##                                                    ##
//########################################################

#include "stdafx.h"
#include "CalcParserTree.h"
#include "..\Tool\Operation.h"


using namespace std;
using namespace XFU;


wstring CalcParserTreeNode::ToString() const
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

wstring CalcParserTreeNodeExpr::ToString() const
{
   return GetChild(0)->ToString() + GetChild(1)->ToString();
}

wstring CalcParserTreeNodeExprTail::ToString() const
{
   if (GetOp().empty())
   {
      return L"";
   }
   else
   {
      return GetOp() + GetChild(0)->ToString() + GetChild(1)->ToString();
   }
}

wstring CalcParserTreeNodeTerm::ToString() const
{
   return GetChild(0)->ToString() + GetChild(1)->ToString();
}

wstring CalcParserTreeNodeTermTail::ToString() const
{
   if (GetOp().empty())
   {
      return L"";
   }
   else
   {
      return GetOp() + GetChild(0)->ToString() + GetChild(1)->ToString();
   }
}

wstring CalcParserTreeNodeFactor::ToString() const
{
   if (HasChild())
   {
      return wstring(L"(") + GetChild(0)->ToString() + wstring(L")");
   }
   else
   {
      return GetNumber();
   }
}


