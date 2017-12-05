//########################################################
//##                                                    ##
//##        Author:    xfu                              ##
//##        E-Mail:    tech@zhongwenshu.de              ##
//##                                                    ##
//########################################################

#include "stdafx.h"
#include "CalcVisitor.h"


using namespace std;
using namespace XFU;



void CalcTreeToString::VisitFactor(const CalcParserTreeNodeFactor* factor)
{
   _oss << factor->ToString();
}

void CalcTreeToString::VisitTerm(const CalcParserTreeNodeTerm* term)
{
   _oss << term->ToString();
}

void CalcTreeToString::VisitTermTail(const CalcParserTreeNodeTermTail* termtail)
{
   _oss << termtail->ToString();
}

void CalcTreeToString::VisitExpr(const CalcParserTreeNodeExpr* expr)
{
   _oss << expr->ToString();
}

void CalcTreeToString::VisitExprTail(const CalcParserTreeNodeExprTail* exprtail)
{
   _oss << exprtail->ToString();
}



std::wstring XFU::run_visitor(const std::shared_ptr<CalcParserTreeNode>& tree)
{
   std::unique_ptr<CalcTreeToString> builder(new CalcTreeToString);
   CalcParserTreeNodeExpr* expr = static_cast<CalcParserTreeNodeExpr*>(tree->GetChild(0).get());
   builder->VisitExpr(expr);

   return builder->GetString();
}