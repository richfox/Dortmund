#pragma once

#include "basedef.h"
#include "Time.h"
#include "Error.h"
#include "logging.h"



#ifdef _DEBUG
   #define CHECK_ERROR(CONDITION,DESCRIPTION) do{if(!(CONDITION))throw XFU::Error(DESCRIPTION);}while(0)
   #define CONSOLE_MESSAGE(TEXT) OutputDebugString(TEXT)
   #define LOG_MESSAGE(FILE,TEXT) XFU::log_message(FILE,TEXT)
   #define ELAPSED_START auto elapsed = XFU::time_call([&]{
   #define ELAPSED_END });
#else
   #define CHECK_ERROR(CONDITION,DESCRIPTION)
   #define CONSOLE_MESSAGE(TEXT)
   #define LOG_MESSAGE(FILE,TEXT)
   #define ELAPSED_START
   #define ELAPSED_END
#endif