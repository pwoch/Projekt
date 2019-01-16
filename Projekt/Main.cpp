/** @file */

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
	string fin_path = "undefined";
	string flekarz_path = "undefined";
	string fpacjent_path = "undefined";
	string nazwisko_pacjenta = "undefined";
	fstream fin;

	for (int i = 1; i < argc; i++)
	{
		if (!strcmp(argv[i], "-fin"))
		{
			fin_path = argv[i + 1];
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
			else
			{
				cout << "B³¹d otwarcia pliku" << endl;
				return -1;
			}
			fin.close();
			break;
		}
		else
		{
			cout << "Nazwa / sciezka pliku wejsciowego nie zostala podana lub jest nieprawidlowa" << endl;
			return -1;
		}
	}
	
	for (int i = 1; i < argc; i++)
	{
		if (!strcmp(argv[i], "-zamieñ"))
		{
			zamienWizyte(gLekarz, gPacjent , argv[i+1], stoul(argv[i+2]));
			i += 2;
		}
		else if (!strcmp(argv[i], "-usuñ"))
		{
			int iloscLekarzy = 0;
			Lekarz * pLekarz = gLekarz;
			while(pLekarz)
			{
				iloscLekarzy++;
				pLekarz = pLekarz->wsk_nastepny_lekarz;
			}
			if (iloscLekarzy > 1) 
			{
				usunLekarza(gLekarz, gPacjent, argv[i + 1]);
			}
			else
			{
				cout << "Nie mozna usunac lekarza, poniewaz jest jedyny i nie mozna przepisac jego wizyt" << endl;
			}
			i++;
		}
		else if (!strcmp(argv[i], "-flekarz"))
		{
			flekarz_path = argv[i+1];
			i++;
		}
		else if (!strcmp(argv[i], "-fpacjent"))
		{
			fpacjent_path = argv[i + 1];
			nazwisko_pacjenta = argv[i + 2];
			i+=2;
		}
		else if (!strcmp(argv[i], "-fin"))
		{
			i++;
		}
		else
		{
			cout << "Niepoprawnie wprowadzony argument nr " << i << endl;
		}
	}

	liczSrednie(gLekarz);

	if (fin_path != "undefined")
	{
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
		else
		{
			cout << "Blad otwarcia pliku lub nieprawidlowa nazwa/sciezka pliku wyjsciowego" << endl;
			return -1;
		}
		fin_updated.close();
	}
	else
	{
		cout << "Blad pliku wyjsciowego - nie podano nazwy/sciezki" << endl;
	}
	
	if (flekarz_path != "undefined")
	{
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
		else
		{
			cout << "Blad otwarcia pliku lub nieprawidlowa nazwa/sciezka pliku flekarz" << endl;
			return -1;
		}
		flekarz.close();

	}
	else
	{
		cout << "Nie podano nazwy/sciezki pliku (flekarz)" << endl;
	}

	if (fpacjent_path != "undefined" && pacjentIstnieje(gPacjent, nazwisko_pacjenta))
	{
		ofstream fpacjent(fpacjent_path);
		if (fpacjent.good())
		{
			Lekarz * pL = gLekarz;
			while (pL)
			{
				Wizyta * pW = pL->head_wizyty;
				while (pW)
				{
					if (pW->nazwisko_pacjenta == nazwisko_pacjenta)
					{
						fpacjent << pW->data_wizyty << ";" << "Pacjent: "<< pW->nazwisko_pacjenta <<" Lekarz: "<<pL->nazwisko<< endl;
					}
					pW = pW->wsk_nastepna_wizyta;
				}
				pL = pL->wsk_nastepny_lekarz;
			}
		}
		else
		{
			cout << "Blad otwarcia pliku lub nieprawidlowa nazwa/sciezka pliku fpacjent" << endl;
			return -1;
		}
		fpacjent.close();
	}
	else
	{
		if (!pacjentIstnieje(gPacjent, nazwisko_pacjenta))
		{
			cout << "Blad zapisu w pliku fpacjent: podany pacjent nie istnieje" << endl;
		}
		else
		{
			cout << "Nie podano nazwy/sciezki pliku (fpacjent)" << endl;
		}
	}

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

	cout << "Zwolniono pamiec. " << endl;
	cout << "Zakonczono program. " << endl;

	system("pause");

	return 0;
}