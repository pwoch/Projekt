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
	zamienWizyte(gLekarz, gPacjent , "pKowalski", 2018101101);
	usunLekarza(gLekarz, gPacjent, "lFrankowski");
	liczSrednie(gLekarz);
	wypisz(gLekarz);
	//
	
	ofstream fin_updated(fin_path);
	if (fin_updated.good()) 
	{
		Lekarz * pL = gLekarz;
		while (pL)
		{
			Wizyta * pW = pL->head_wizyty;
			while (pW)
			{
				fin_updated << pW->data_wizyty << ";" << pW->nazwisko_pacjenta << ";" << pL->nazwisko << endl;
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
		//TODO
	}
	fpacjent.close();

	

	//TODO: Zwolnienie pamieci -> usuniecie list itp.
	//TODO: Dokumentacja doxygen
	system("pause");

	return 0;
}