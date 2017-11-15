//########################################################
//##                                                    ##
//##        Author:    xfu                              ##
//##        E-Mail:    tech@zhongwenshu.de              ##
//##                                                    ##
//########################################################

//四则运算词法分析器
//只允许四则运算符，数字和括号，允许有空格！
//tokenizer("(11+22)*33") -> ["(","11","+","22",")","*","33"]

#pragma once
#include <string>
#include <vector>

namespace XFU
{
   enum class TokenStatus
   {
      TokenStatusNotDefined = -1,
      TokenNumber,
      TokenOperator,
      TokenParenthesis
   };

   class Tokenizer
   {
   public:
      Tokenizer(const std::wstring& text)
         :_text(text),
         _status(TokenStatus::TokenStatusNotDefined),
         _token()
      {}

      ~Tokenizer()
      {}

      //run tokenizer, return a vector of token
      std::vector<std::wstring> Run();
      
   private:
      bool IsNumber(std::wstring::const_iterator it);
      bool IsOperator(std::wstring::const_iterator it);
      bool IsParenthesis(std::wstring::const_iterator it);
      bool IsWhiteSpace(std::wstring::const_iterator it);
      bool IsValid(std::wstring::const_iterator it);

   private:
      std::wstring _text;
      TokenStatus _status;
      std::wstring _token;
   };

   std::vector<std::wstring> __declspec(dllexport) run_tokenizer(const std::wstring& text);
}