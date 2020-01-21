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

namespace XFU
{
   class LogisTokenizer
   {
   public:
      LogisTokenizer(const std::wstring& expr)
         :_expr(expr)
      {}

      ~LogisTokenizer()
      {}

      std::vector<std::wstring> Run();

   private:
      bool IsOperator(std::wstring::const_iterator it)
      {
         return *it==L'+';
      }

      bool IsParenthesis(std::wstring::const_iterator it)
      {
         return *it==L'(' || *it==L')';
      }

      bool IsWhiteSpace(std::wstring::const_iterator it)
      {
         return *it == L' ';
      }

      bool IsKeyword(std::wstring::const_iterator it)
      {
         wregex rx(L"^%[a-zA-Z0-9]+$");
         return regex_search(wstring(1,*it),rx);
      }

      bool IsText(std::wstring::const_iterator it)
      {
         wregex rx(L"^[a-zA-Z0-9]+$");
         return regex_search(wstring(1,*it),rx);
      }

      bool IsHeader(std::wstring::const_iterator it)
      {
         wregex rx(L"^[a-zA-Z0-9]+$");
         return regex_search(wstring(1,*it),rx);
      }

      bool IsSn(std::wstring::const_iterator it)
      {
         wregex rx(L"^[a-zA-Z0-9\-]+$");
         return regex_search(wstring(1,*it),rx);
      }

      bool IsValid(std::wstring::const_iterator it)
      {
         return IsOperator(it) || 
                IsParenthesis(it) || 
                IsWhiteSpace(it) || 
                IsKeyword(it) || 
                IsText(it) ||
                IsHeader(it) ||
                IsSn(it);
      }

   private:
      std::wstring _expr;
   };
}