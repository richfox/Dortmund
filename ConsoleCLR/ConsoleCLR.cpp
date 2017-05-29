// ConsoleCLR.cpp: Hauptprojektdatei.

#include "stdafx.h"

using namespace System;
using namespace LibraryCS;

int main(array<String ^> ^args)
{
    IndexerClass^ ic = gcnew IndexerClass;
	ic->default[0] = 21;

	for (int i=0; i<=10; i++)
	{
		Console::WriteLine("Element #{0} = {1}",i,ic->default[i]);
	}

    return 0;
}
