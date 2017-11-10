//########################################################
//##                                                    ##
//##        Author:    xfu                              ##
//##        E-Mail:    tech@zhongwenshu.de              ##
//##                                                    ##
//########################################################

//四则运算语法分析器

//递归下降的语法:
//Expr   ->  Term + Expr
//       |   Term - Expr
//       |   Term
//Term   ->  Factor * Term
//       |   Factor / Term
//       |   Factor
//Factor ->  (Expr)
//       |   num

//根据语法生成语法树AST

#pragma once
#include <string>
#include <vector>


namespace XFU
{
   class Parser
   {
   public:
      Parser(const std::vector<std::wstring>& tokens)
         :_tokenit(tokens.begin())
      {}

      ~Parser()
      {}

      bool Run();

   private:
      void NextToken();

   private:
      std::vector<std::wstring>::const_iterator _tokenit;
   };
}
