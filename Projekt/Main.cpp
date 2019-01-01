#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Nag³ówek.h"
#include <cstdlib>
#include <crtdbg.h>

#define _CRTDBG_MAP_ALLOC
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace std;

int main()
{
	vector<unsigned long> daty_vec;
	string fin_path = "D:\wizyty.txt";
	fstream fin;
	fin.open(fin_path);
	if (fin.good())
	{
		string wiersz;
		vector<string> wizyta_vec;

		Lekarz * gLekarz = NULL;
		Pacjent * gPacjent = NULL;

		while (!fin.eof())
		{
			getline(fin, wiersz);
			wizyta_vec = pobierz(wiersz);
			unsigned long data = 0;
			string l_nazwisko;
			string p_nazwisko;

			try 
			{
				data = stoul(wizyta_vec[0]);
			}
			catch (exception e) 
			{
				cout << "Z³y format daty w pliku wejœciowym. Data: " << wizyta_vec[0] << endl;
				return -1;
			}

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
	

	//TODO: Zwolnienie pamieci -> usuniecie list itp.
	//TODO: Sprawdzanie wyciekow pamieci
	//TODO: Dokumentacja doxygen
	system("pause");

	return 0;
}