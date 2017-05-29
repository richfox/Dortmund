// Utility.cpp : Definiert die exportierten Funktionen für die DLL-Anwendung.
//

#include "stdafx.h"
#include "Utility.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Das einzige Anwendungsobjekt

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		// MFC initialisieren und drucken. Bei Fehlschlag Fehlermeldung aufrufen.
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO: Den Fehlercode an Ihre Anforderungen anpassen.
			_tprintf(_T("Schwerwiegender Fehler bei der MFC-Initialisierung\n"));
			nRetCode = 1;
		}
		else
		{
			// TODO: Hier den Code für das Verhalten der Anwendung schreiben.
		}
	}
	else
	{
		// TODO: Den Fehlercode an Ihre Anforderungen anpassen.
		_tprintf(_T("Schwerwiegender Fehler: Fehler bei GetModuleHandle.\n"));
		nRetCode = 1;
	}

	return nRetCode;
}
