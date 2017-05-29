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

#pragma once

#include <string>
#include "basedef.h"


#pragma warning (push)
#pragma warning (disable: 4251)

namespace XFU
{
   class UTIL_CLASS RegWriter
   {
   public:
      RegWriter(const std::wstring& regkey);
      ~RegWriter();

      bool WriteValueToReg(const std::wstring& subkey,const DWORD& value);
      bool ReadValueFromReg(const std::wstring& subkey,DWORD& value);

      bool WriteByteToReg(const std::wstring& subkey,const BYTE& value);
      bool ReadByteFromReg(const std::wstring& subkey,BYTE& value);

      bool WriteStrToReg(const std::wstring& subkey,const std::wstring& value);
      bool ReadStrFromReg(const std::wstring& subkey,std::wstring& value);

   private:
      const std::wstring _regkey;
   };
}

#pragma warning (pop)