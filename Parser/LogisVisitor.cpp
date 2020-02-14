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