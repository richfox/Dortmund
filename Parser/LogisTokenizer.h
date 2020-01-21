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
      bool IsOperator(std::wstring::const_iterator it);

   private:
      std::wstring _expr;
   };
}