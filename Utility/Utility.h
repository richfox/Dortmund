// Folgender ifdef-Block ist die Standardmethode zum Erstellen von Makros, die das Exportieren 
// aus einer DLL vereinfachen. Alle Dateien in dieser DLL werden mit dem UTILITY_EXPORTS-Symbol
// (in der Befehlszeile definiert) kompiliert. Dieses Symbol darf f�r kein Projekt definiert werden,
// das diese DLL verwendet. Alle anderen Projekte, deren Quelldateien diese Datei beinhalten, erkennen 
// UTILITY_API-Funktionen als aus einer DLL importiert, w�hrend die DLL
// mit diesem Makro definierte Symbole als exportiert ansieht.
#ifdef UTILITY_EXPORTS
#define UTILITY_API __declspec(dllexport)
#else
#define UTILITY_API __declspec(dllimport)
#endif

// Diese Klasse wird aus Utility.dll exportiert.
class UTILITY_API CUtility {
public:
	CUtility(void);
	// TODO: Hier die Methoden hinzuf�gen.
};

extern UTILITY_API int nUtility;

UTILITY_API int fnUtility(void);
