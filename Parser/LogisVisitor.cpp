//########################################################
//##                                                    ##
//##        Author:    xfu                              ##
//##        E-Mail:    tech@zhongwenshu.de              ##
//##                                                    ##
//########################################################

#include "stdafx.h"
#include "LogisVisitor.h"


using namespace std;
using namespace logis;


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
   LogisTreeNodeExp* exp = static_cast<LogisTreeNodeExp*>(tree->GetChild(0).get());
   builder->VisitExp(exp);

   return builder->GetString();
}