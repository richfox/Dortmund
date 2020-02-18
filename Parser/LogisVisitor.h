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
#include "LogisTree.h"


namespace logis
{
   class LogisVisitor
   {
   protected:
      LogisVisitor()
      {}

   public:
      virtual ~LogisVisitor()
      {}

      virtual void VisitNode(const LogisTreeNode* node) = 0;
      virtual void VisitExp(const LogisTreeNodeExp* exp) = 0;
      virtual void VisitKeyExp(const LogisTreeNodeKeyExp* kexp) = 0;
      virtual void VisitPrimeExp(const LogisTreeNodePrimeExp* pexp) = 0;
      virtual void VisitText(const LogisTreeNodeText* text) = 0;
   };


   class LogisTreeToString : public LogisVisitor
   {
   public:
      LogisTreeToString()
         :LogisVisitor(),
         _oss()
      {}

      virtual ~LogisTreeToString()
      {}

      std::wstring GetString() const
      {
         return _oss.str();
      }

      virtual void VisitNode(const LogisTreeNode* node) override;
      virtual void VisitExp(const LogisTreeNodeExp* exp) override;
      virtual void VisitKeyExp(const LogisTreeNodeKeyExp* kexp) override;
      virtual void VisitPrimeExp(const LogisTreeNodePrimeExp* pexp) override;
      virtual void VisitText(const LogisTreeNodeText* text) override;

   private:
      std::wostringstream _oss;
   };


   class LogisTreeSearch : public LogisVisitor
   {
   public:
      LogisTreeSearch(const std::wstring& sn)
         :LogisVisitor(),
         _sn(sn)
      {}

      virtual void VisitNode(const LogisTreeNode* node) override;
      virtual void VisitExp(const LogisTreeNodeExp* exp) override;
      virtual void VisitKeyExp(const LogisTreeNodeKeyExp* kexp) override;
      virtual void VisitPrimeExp(const LogisTreeNodePrimeExp* pexp) override;
      virtual void VisitText(const LogisTreeNodeText* text) override;


   private:
      std::wstring _sn;
      bool _found;
   };

   std::wstring __declspec(dllexport) run_logis_visitor(const std::shared_ptr<LogisTreeNode>& tree);
}