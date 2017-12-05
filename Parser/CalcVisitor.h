//########################################################
//##                                                    ##
//##        Author:    xfu                              ##
//##        E-Mail:    tech@zhongwenshu.de              ##
//##                                                    ##
//########################################################


#pragma once

#include <memory>
#include <sstream>
#include <string>
#include "CalcParserTree.h"


namespace XFU
{
   class CalcVisitor
   {
   protected:
      CalcVisitor()
      {}

   public:
      virtual ~CalcVisitor()
      {}

      virtual void VisitFactor(const CalcParserTreeNodeFactor* factor) = 0;
      virtual void VisitTerm(const CalcParserTreeNodeTerm* term) = 0;
      virtual void VisitTermTail(const CalcParserTreeNodeTermTail* termtail) = 0;
      virtual void VisitExpr(const CalcParserTreeNodeExpr* expr) = 0;
      virtual void VisitExprTail(const CalcParserTreeNodeExprTail* exprtail) = 0;
   };

   class CalcTreeToString : public CalcVisitor
   {
   public:
      CalcTreeToString()
         :CalcVisitor(),
         _oss()
      {}

      virtual ~CalcTreeToString()
      {}

      std::wstring GetString() const
      {
         return _oss.str();
      }

      virtual void VisitFactor(const CalcParserTreeNodeFactor* factor) override;
      virtual void VisitTerm(const CalcParserTreeNodeTerm* term) override;
      virtual void VisitTermTail(const CalcParserTreeNodeTermTail* termtail) override;
      virtual void VisitExpr(const CalcParserTreeNodeExpr* expr) override;
      virtual void VisitExprTail(const CalcParserTreeNodeExprTail* exprtail) override;

   private:
      std::wostringstream _oss;
   };

   std::wstring __declspec(dllexport) run_visitor(const std::shared_ptr<CalcParserTreeNode>& tree);
}