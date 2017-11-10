//########################################################
//##                                                    ##
//##        Author:    xfu                              ##
//##        E-Mail:    tech@zhongwenshu.de              ##
//##                                                    ##
//########################################################

// Tokenizer.cpp

#include "stdafx.h"
#include "CalcTokenizer.h"
#include <regex>
#include <memory>


using namespace std;
using namespace XFU;



vector<wstring> Tokenizer::Run()
{
   vector<wstring> tokens;

   for (wstring::const_iterator it=_text.begin(); it!=_text.end(); it++)
   {
      if (!IsValid(it))
      {
         throw runtime_error("invalid input");
      }

      if (IsWhiteSpace(it))
      {
         if (it == _text.end() - 1)
         {
            tokens.push_back(_token);
            _status = TokenStatus::TokenStatusNotDefined;
         }
         continue;
      }

      if (IsNumber(it))
      {
         if (_status!=TokenStatus::TokenNumber && _token.length()>0)
         {
            tokens.push_back(_token);
            _token.assign(1,*it);
         }
         else
         {
            _token.append(1,*it);
         }
         _status = TokenStatus::TokenNumber;
      }

      if (IsOperator(it))
      {
         if (_status!=TokenStatus::TokenOperator && _token.length()>0)
         {
            tokens.push_back(_token);
         }
         _token.assign(1,*it);
         _status = TokenStatus::TokenOperator;
      }

      if (IsParenthesis(it))
      {
         if (_status!=TokenStatus::TokenParenthesis && _token.length()>0)
         {
            tokens.push_back(_token);
         }
         _token.assign(1,*it);
         _status = TokenStatus::TokenParenthesis;
      }

      if (it == _text.end() - 1)
      {
         tokens.push_back(_token);
         _status = TokenStatus::TokenStatusNotDefined;
      }
   }

   return tokens;
}


bool Tokenizer::IsNumber(std::wstring::const_iterator it)
{
   wregex rx(L"^[0-9]+$");
   return regex_search(wstring(1,*it),rx);
}

bool Tokenizer::IsOperator(std::wstring::const_iterator it)
{
   return *it==L'+' || *it==L'-' || *it==L'*' || *it==L'/';
}

bool Tokenizer::IsParenthesis(std::wstring::const_iterator it)
{
   return *it==L'(' || *it==L')';
}

bool Tokenizer::IsWhiteSpace(std::wstring::const_iterator it)
{
   return *it == L' ';
}

bool Tokenizer::IsValid(wstring::const_iterator it)
{
   return IsNumber(it) || IsOperator(it) || IsParenthesis(it) || IsWhiteSpace(it);
}


vector<wstring> XFU::run_tokenizer(const std::wstring& text)
{
   std::unique_ptr<Tokenizer> tokenizer(new Tokenizer(text));
   return tokenizer->Run();
}