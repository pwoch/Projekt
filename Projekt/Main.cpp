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

int main(int argc, char * argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//TODO: argumenty wiersza poleceñ -> pozniej if, nie switch...
	//TODO: sprawdziæ usuwanie lekarza który nie istnieje i przepisanie wizyty która nie istnieje

	vector<unsigned long> daty_vec;
	Lekarz * gLekarz = NULL;
	Pacjent * gPacjent = NULL;
	string fin_path = "D:\wizyty.txt";
	string flekarz_path = "D:\lekarz.txt";
	string fpacjent_path = "D:\pacjent.txt";
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

			if (!pacjentIstnieje(gPacjent, p_nazwisko))
			{
				dodajPacjenta(gPacjent, p_nazwisko);
			}

			dodajWizyte(gLekarz, gPacjent, l_nazwisko, data, p_nazwisko);
		}
	}
	fin.close();

	//
	wypisz(gLekarz);
	cout << endl;
	//zamienWizyte(gLekarz, gPacjent , "pKowalski", 2018101101);
	//usunLekarza(gLekarz, gPacjent, "lFrankowski");
	liczSrednie(gLekarz);
	wypisz(gLekarz);
	//
	
	ofstream fin_updated(fin_path);
	if (fin_updated.good()) 
	{
		int iterator = 0;
		Lekarz * pL = gLekarz;
		while (pL)
		{
			Wizyta * pW = pL->head_wizyty;
			while (pW)
			{
				if (iterator != 0) 
				{
					fin_updated << endl;
				}
				fin_updated << pW->data_wizyty << ";" << pW->nazwisko_pacjenta << ";" << pL->nazwisko;
				++iterator;
				pW = pW->wsk_nastepna_wizyta;
			}
			pL = pL->wsk_nastepny_lekarz;
		}
	}
	fin_updated.close();

	ofstream flekarz(flekarz_path);
	if (flekarz.good()) 
	{
		Lekarz * pL = gLekarz;
		while (pL)
		{
			flekarz << "Srednia wizyt dla lekarza " << pL->nazwisko << ": " << pL->œrednia << endl;
			pL = pL->wsk_nastepny_lekarz;
		}
	}
	flekarz.close();

	ofstream fpacjent(fpacjent_path);
	if (fpacjent.good())
	{
		Lekarz * pL = gLekarz;
		while (pL)
		{
			Wizyta * pW = pL->head_wizyty;
			while (pW)
			{
				fin_updated << pW->data_wizyty << ";" << pW->nazwisko_pacjenta << endl;
				pW = pW->wsk_nastepna_wizyta;
			}
			pL = pL->wsk_nastepny_lekarz;
		}
	}
	fpacjent.close();

	Pacjent * pacjent_tmp = NULL;
	while (gPacjent) 
	{
		pacjent_tmp = gPacjent->wsk_nastepny_pacjent;
		delete gPacjent;
		gPacjent = pacjent_tmp;
	}
	delete pacjent_tmp;

	Lekarz * lekarz_tmp = NULL;
	while (gLekarz) 
	{
		Wizyta * wizyta_tmp = NULL;
		while (gLekarz->head_wizyty) 
		{
			wizyta_tmp = gLekarz->head_wizyty->wsk_nastepna_wizyta;
			delete gLekarz->head_wizyty;
			gLekarz->head_wizyty = wizyta_tmp;
		}
		lekarz_tmp = gLekarz->wsk_nastepny_lekarz;
		delete gLekarz;
		gLekarz = lekarz_tmp;
		delete wizyta_tmp;
	}
	delete lekarz_tmp;

	//TODO: Dokumentacja doxygen
	system("pause");

	return 0;
}