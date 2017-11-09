// stdafx.h : Includedatei für Standardsystem-Includedateien
// oder häufig verwendete projektspezifische Includedateien,
// die nur in unregelmäßigen Abständen geändert werden.
//

#pragma once

// TODO: Hier auf zusätzliche Header, die das Programm erfordert, verweisen.

#ifdef _DEBUG
#using "..\..\install\Debug\LibraryCS.dll"
#else
#using "..\..\install\Release\LibraryCS.dll"
#endif