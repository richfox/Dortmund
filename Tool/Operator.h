#pragma once




#define FOR_INDEX(TYPE,VAR,VALUE)\
   if(bool __scope_flag__=true)\
      for(TYPE VAR = VALUE;__scope_flag__;__scope_flag__=false)

#define FOR_OPERATOR(TYPE,IT,VAR,INDEX)\
   FOR_INDEX(int,INDEX,0)\
   for (TYPE::const_iterator IT=VAR.begin(); IT!=VAR.end(); IT++,INDEX++)