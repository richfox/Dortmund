//########################################################
//##                                                    ##
//##        Author:    xfu                              ##
//##        E-Mail:    tech@zhongwenshu.de              ##
//##                                                    ##
//########################################################

//四则运算语法分析器

//递归下降分析器的构造方法就是为每一个非终结符写一个递归函数，
//函数中对该非终结符可能转换成的所有情况的第一个token进行判断，然后做出对应的处理
//递归下降的语法:
//Expr   ->  Term + Expr
//       |   Term - Expr
//       |   Term
//Term   ->  Factor * Term
//       |   Factor / Term
//       |   Factor
//Factor ->  (Expr)
//       |   num

//<=>

//消除左递归和右递归后的语法
//Expr     -> Term ExprTail
//ExprTail -> + Term ExprTail
//         |  - Term ExprTail
//         |  null
//Term     -> Factor TermTail
//TermTail -> * Factor TermTail
//         |  / Factor TermTail
//         |  null
//Factor   -> (Expr)
//         |  num

//根据语法生成语法树AST
//  (四则运算表达式的根 3*(1+2) ) 
//    |       |           |
// Factor     op       Factor       
//    |       |        /  |  \       
//    3       *       ( Expr  )     
//                     /  | \
//                 Factor op Factor      
//                   |    |    |    
//                   1    +    2  


#pragma once
#include <string>
#include <vector>
#include <memory>


namespace XFU
{
   class CalcParserTreeNode;

   class Parser
   {
   public:
      Parser(const std::vector<std::wstring>& tokens)
         :_tokens(tokens),
         _tokenit(),
         _success(false),
         _currentnode()
      {}

      ~Parser()
      {}

      //run parser, return a syntax tree
      std::shared_ptr<CalcParserTreeNode> Run();

      bool IsSuccess() const
      {
         return _success;
      }

   private:
      bool Expr();
      bool ExprTail();
      bool Term();
      bool TermTail();
      bool Factor();

      bool Number();
      bool NextToken();

   private:
      std::vector<std::wstring> _tokens;
      std::vector<std::wstring>::const_iterator _tokenit;
      bool _success;
      CalcParserTreeNode* _currentnode;
   };


   bool __declspec(dllexport) test_parser(const std::vector<std::wstring>& tokens);
   std::shared_ptr<CalcParserTreeNode> __declspec(dllexport) run_parser(const std::vector<std::wstring>& tokens);
}
