// stdafx.h : Includedatei für Standardsystem-Includedateien
// oder häufig verwendete projektspezifische Includedateien,
// die nur in unregelmäßigen Abständen geändert werden.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Selten verwendete Teile der Windows-Header nicht einbinden.
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // Einige CString-Konstruktoren sind explizit.
#define _AFX_NO_MFC_CONTROLS_IN_DIALOGS         // Unterstützung für MFC-Steuerelemente in Dialogfeldern entfernen

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Selten verwendete Teile der Windows-Header nicht einbinden.
#endif

#include <afx.h>
#include <afxwin.h>         // MFC-Kern- und Standardkomponenten
#include <afxext.h>         // MFC-Erweiterungen
#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC-Unterstützung für allgemeine Steuerelemente von Internet Explorer 4
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>                     // MFC-Unterstützung für allgemeine Windows-Steuerelemente
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <iostream>
// Windows-Headerdateien:
#include <windows.h>



// TODO: Hier auf zusätzliche Header, die das Programm erfordert, verweisen.
#include <vector>
#include <list>
#include <tuple>
#include <string>
#include <map>
#include <limits>
#include <math.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <set>
#include <memory>
#include <regex>
#include <functional>
#include <iomanip>
#include <ppl.h>
#include <tuple>