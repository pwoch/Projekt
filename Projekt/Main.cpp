#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>
#include <winbase.h>
#include "Nag³ówek.h"
#include <cstdlib>
#include <crtdbg.h>

#define _CRTDBG_MAP_ALLOC

using namespace std;

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	vector<unsigned long> daty_vec;
	Lekarz * gLekarz = NULL;
	Pacjent * gPacjent = NULL;
	string fin_path = "D:\wizyty.txt";
	fstream fin;
	fin.open(fin_path);
	if (fin.good())
	{
		string wiersz;
		vector<string> wizyta_vec;

		while (!fin.eof())
		{
			getline(fin, wiersz);
			wizyta_vec = pobierz(wiersz);
			unsigned long data = 0;
			string l_nazwisko;
			string p_nazwisko;

			data = stoul(wizyta_vec[0]);

			p_nazwisko = wizyta_vec[1];
			l_nazwisko = wizyta_vec[2];

			if (!lekarzIstnieje(gLekarz, l_nazwisko))
			{
				dodajLekarza(gLekarz, l_nazwisko);
			}

			dodajWizyte(gLekarz, gPacjent, l_nazwisko, data, p_nazwisko);
		}
	}
	fin.close();

	wypisz(gLekarz);

	//TODO: Zwolnienie pamieci -> usuniecie list itp.
	//TODO: Dokumentacja doxygen
	system("pause");

	return 0;
}