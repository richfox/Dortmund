#pragma once

#include "basedef.h"
#include "Time.h"
#include "Error.h"



#ifdef _DEBUG
   #define CHECK_ERROR(CONDITION,DESCRIPTION) do{if(!(CONDITION))throw XFU::Error(DESCRIPTION);}while(0)
   #define LOGMESSAGE(TEXT) OutputDebugString(TEXT)
   #define ELAPSED_START auto elapsed = XFU::time_call([&]{
   #define ELAPSED_END });
#else
   #define CHECK_ERROR(CONDITION,DESCRIPTION)
   #define LOGMESSAGE(TEXT)
   #define ELAPSED_START
   #define ELAPSED_END
#endif