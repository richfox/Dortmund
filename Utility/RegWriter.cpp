//########################################################
//##                                                    ##
//##        Product:   HiCAD / HeLIOS                   ##
//##        Copyright: by ISD Software & Systeme GmbH   ##
//##        Adress:    Hauert 4                         ##
//##                   44227 Dortmund                   ##
//##                   Germany                          ##
//##        Phone:      (+49) 231 97 93 0               ##
//##        E-Mail:     info@isdCAD.de                  ##
//##                                                    ##
//########################################################
#include "stdafx.h"
#include "RegWriter.h"

using namespace std;
using namespace XFU;


RegWriter::RegWriter(const std::wstring& regkey)
   :_regkey(regkey)
{

}

RegWriter::~RegWriter()
{

}

bool RegWriter::WriteValueToReg(const std::wstring& subkey,const DWORD& value)
{
   bool res = false;

   HKEY hk;
   DWORD dpos;
   if (RegCreateKeyEx(HKEY_CURRENT_USER,_regkey.c_str(),0,NULL,REG_OPTION_NON_VOLATILE,KEY_WRITE,NULL,&hk,&dpos) == ERROR_SUCCESS)
   {
      if (RegSetValueEx(hk,subkey.c_str(),0,REG_DWORD,LPBYTE(&value),sizeof(DWORD)) == ERROR_SUCCESS)
         res = true;

      RegCloseKey(hk);
   }

   return res;
}

bool RegWriter::ReadValueFromReg(const std::wstring& subkey,DWORD& value)
{
   bool res = false;

   HKEY hk;
   if (RegOpenKeyEx(HKEY_CURRENT_USER,_regkey.c_str(),0,KEY_READ,&hk) == ERROR_SUCCESS)
   {
      DWORD type;
      DWORD size = sizeof(DWORD);
      if (RegQueryValueEx(hk,subkey.c_str(),0,&type,LPBYTE(&value),&size) == ERROR_SUCCESS)
         res = true;

      RegCloseKey(hk);
   }

   return res;
}

bool RegWriter::WriteByteToReg(const std::wstring& subkey,const BYTE& value)
{
   bool res = false;

   HKEY hk;
   DWORD dpos;
   if (RegCreateKeyEx(HKEY_CURRENT_USER,_regkey.c_str(),0,NULL,REG_OPTION_NON_VOLATILE,KEY_WRITE,NULL,&hk,&dpos) == ERROR_SUCCESS)
   {
      if (RegSetValueEx(hk,subkey.c_str(),0,REG_BINARY,&value,sizeof(BYTE)) == ERROR_SUCCESS)
         res = true;

      RegCloseKey(hk);
   }

   return res;
}

bool RegWriter::ReadByteFromReg(const std::wstring& subkey,BYTE& value)
{
   bool res = false;

   HKEY hk;
   if (RegOpenKeyEx(HKEY_CURRENT_USER,_regkey.c_str(),0,KEY_READ,&hk) == ERROR_SUCCESS)
   {
      DWORD type;
      DWORD size = sizeof(BYTE);
      if (RegQueryValueEx(hk,subkey.c_str(),0,&type,&value,&size) == ERROR_SUCCESS)
         res = true;

      RegCloseKey(hk);
   }

   return res;
}

bool RegWriter::WriteStrToReg(const std::wstring& subkey,const std::wstring& value)
{
   bool res = false;

   HKEY hk;
   DWORD dpos;
   if (RegCreateKeyEx(HKEY_CURRENT_USER,_regkey.c_str(),0,NULL,REG_OPTION_NON_VOLATILE,KEY_WRITE,NULL,&hk,&dpos) == ERROR_SUCCESS)
   {
      if (RegSetValueEx(hk,subkey.c_str(),0,REG_SZ,LPBYTE(value.c_str()),static_cast<DWORD>(value.size()+1)) == ERROR_SUCCESS)
         res = true;

      RegCloseKey(hk);	
   }

   return res;
}

bool RegWriter::ReadStrFromReg(const std::wstring& subkey,std::wstring& value)
{
   bool res = false;

   HKEY hk;
   if (RegOpenKeyEx(HKEY_CURRENT_USER,_regkey.c_str(),0,KEY_READ,&hk) == ERROR_SUCCESS)
   {
      DWORD type;
      wchar_t data[256] = L"";
      DWORD size = sizeof(wchar_t) * _countof(data);
      if (RegQueryValueEx(hk,subkey.c_str(),0,&type,LPBYTE(data),&size) == ERROR_SUCCESS)
      {
         value.assign(data);
         res = true;
      }

      RegCloseKey(hk);
   }

   return res;
}