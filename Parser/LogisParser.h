//########################################################
//##                                                    ##
//##        Author:    xfu                              ##
//##        E-Mail:    tech@zhongwenshu.de              ##
//##                                                    ##
//########################################################

//物流表达式
//%铁路(中通6666 + 圆通YT(8888 + 5641)) + %空运(JD0001-1-1)

#pragma once

#include <string>
#include <vector>
#include <memory>


namespace XFU
{
   class LogisTreeNode;

   class LogisParser
   {
   public:
      LogisParser(const std::vector<std::wstring>& tokens)
         :_tokens(tokens),
         _tokenit(),
         _success(false),
         _currentnode(nullptr)
      {}

      ~LogisParser()
      {}

      std::shared_ptr<LogisTreeNode> Run();

      bool IsSuccess() const
      {
         return _success;
      }

   private:
      bool Exp();
      bool Exp1();
      bool Exp2();
      bool Text();
      bool Factor();
      bool Tail();
      bool Keyword();
      bool Header();
      bool Sn();

      bool NextToken();

   private:
      std::vector<std::wstring> _tokens;
      std::vector<std::wstring>::const_iterator _tokenit;
      bool _success;
      LogisTreeNode* _currentnode;
   };


   bool __declspec(dllexport) test_logis_parser(const std::vector<std::wstring>& tokens);
   std::shared_ptr<LogisTreeNode> __declspec(dllexport) run_logis_parser(const std::vector<std::wstring>& tokens);
}