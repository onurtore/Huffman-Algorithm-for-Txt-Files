//============================================================================
// Name        : Term Project Spring 2016
// Author      : Onur Berk Tore
// Version     : 3.561.12.34565.44645.756.895
// Copyright   : None
// Description : C++
//============================================================================


#include <iostream>
#include <Windows.h>

#include "Header.h"

using namespace std;

int main() {

	//char(999) = 'ç' choosen as a Dummy EOF Character.

	SetConsoleTitle(TEXT("DATA STRUCTURE PROJECT BY ONUR BERK TORE"));

	DataProject HeilHydra;

	HeilHydra.menu();
	
	system("PAUSE");
}