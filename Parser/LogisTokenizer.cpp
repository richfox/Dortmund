//########################################################
//##                                                    ##
//##        Author:    xfu                              ##
//##        E-Mail:    tech@zhongwenshu.de              ##
//##                                                    ##
//########################################################

//物流表达式
//%铁路(中通6666 + 圆通YT(8888 + 5641)) + %空运(JD0001-1-1)

#include "stdafx.h"
#include "LogisTokenizer.h"
#include <regex>
#include <memory>


using namespace std;
using namespace XFU;


vector<wstring> LogisTokenizer::Run()
{
   vector<wstring> tokens;

   for (wstring::const_iterator it=_expr.begin(); it!=_expr.end(); it++)
   {

   }

   return tokens;
}