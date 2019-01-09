#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>
#include <winbase.h>
#include "Nag³ówek.h"


using namespace std;

vector <string> pobierz (string input)
{
	int iterator = 0;
	int index = 0;
	vector<string> wizyta_vec;
	string wizyta_tab[3]{"", "", ""};

	while (iterator < input.length())
	{
		if (input[iterator] != ';')
		{
			wizyta_tab[index] += input[iterator];
		}
		else
		{
			++index;
		}
		++iterator;
	}

	wizyta_vec.push_back(wizyta_tab[0]);
	wizyta_vec.push_back(wizyta_tab[1]); 
	wizyta_vec.push_back(wizyta_tab[2]);

	return wizyta_vec;
}

bool lekarzIstnieje(Lekarz * gLekarz, string l_nazwisko)
{
	while (gLekarz)
	{
		if (gLekarz->nazwisko == l_nazwisko)
		{
			return true;
		}
		gLekarz = gLekarz->wsk_nastepny_lekarz;
	}
	return false;
}

void dodajLekarza(Lekarz * & gLekarz, string l_nazwisko)
{
	gLekarz = new Lekarz{ l_nazwisko,0, gLekarz,NULL };
}

bool pacjentIstnieje(Pacjent * gPacjent, string p_nazwisko)
{
	while (gPacjent)
	{
		if (gPacjent->nazwisko == p_nazwisko)
		{
			return true;
		}
		gPacjent = gPacjent->wsk_nastepny_pacjent;
	}
	return false;
}

void dodajPacjenta(Pacjent * & gPacjent, string p_nazwisko)
{
	gPacjent = new Pacjent{ p_nazwisko, gPacjent};
}

void dodajWizyte(Lekarz * gLekarz, Pacjent * gPacjent, string l_nazwisko,unsigned long data_wizyty, string p_nazwisko)
{
	Pacjent * tmpPacjent = NULL;
	while (gPacjent)
	{
		if (p_nazwisko == gPacjent->nazwisko)
		{
			tmpPacjent = gPacjent;
		}
		gPacjent = gPacjent->wsk_nastepny_pacjent;
	}
	while (gLekarz)
	{
		if (l_nazwisko == gLekarz->nazwisko)
		{
			
			gLekarz->head_wizyty = new Wizyta{data_wizyty,p_nazwisko,tmpPacjent,gLekarz->head_wizyty};
		}
		gLekarz = gLekarz->wsk_nastepny_lekarz;
	}
}

void usunKonkretnaWizyte(Lekarz * gLekarz, Wizyta * & head_wizyty, string pacjent, unsigned long data)
{
	Wizyta * p, *poprzedni;
	poprzedni = NULL;
	for (p = gLekarz->head_wizyty; p != NULL; poprzedni = p, p = p->wsk_nastepna_wizyta)
	{
		if (p->nazwisko_pacjenta == pacjent and p->data_wizyty == data)
		{
			if (poprzedni == NULL)
			{
				gLekarz->head_wizyty = p->wsk_nastepna_wizyta;
			}
			else
			{
				poprzedni->wsk_nastepna_wizyta = p->wsk_nastepna_wizyta;
			}
			delete p;
		}
		else
		{
			cout << "Nie ma takiej wizyty" << endl;
		}
	}
}

void zamienWizyte(Lekarz * gLekarz, Pacjent * gPacjent, string pacjent, unsigned long data)
{
	usunKonkretnaWizyte(gLekarz, gLekarz->head_wizyty, pacjent, data);
	while (gLekarz)
	{
		Wizyta * p = gLekarz->head_wizyty;
		data += 100;
		while (p)
		{
			if (p->data_wizyty != data)
			{
				dodajWizyte(gLekarz, gPacjent,gLekarz->nazwisko ,data, pacjent);
			}
			else
			{
				data += 10;
			}
			p = p->wsk_nastepna_wizyta;
		}
		gLekarz = gLekarz->wsk_nastepny_lekarz;
	}
}

unsigned long pobierzCzas()
{
	SYSTEMTIME st;
	GetSystemTime(&st);
	int r = st.wYear;
	int m = st.wMonth;
	int d = st.wDay;
	string rok = to_string(r);
	string miesiac = to_string(m);
	string dzien = to_string(d);
	string aktualna_data = rok + miesiac + dzien + "00";
	unsigned long data = stoul(aktualna_data);
	return data;
}

void usunLekarza(Lekarz * & gLekarz, string lekarz)
{
	Lekarz * pL = gLekarz;
	unsigned long obecna_data = pobierzCzas();
	while (pL)
	{
		if (gLekarz->nazwisko == lekarz)
		{
			Wizyta * pW = pL->head_wizyty;
			while (pW)
			{
				if (pW->data_wizyty < obecna_data)
				{
					pL->head_wizyty = pW;
					delete pW;
				}
				else
				{
					if (gLekarz->nazwisko != lekarz) //TODO: dokonczyc funkcje

					{
						//dodaj najbli¿szy termin wizyty
						//usuñ pL->head_wizyty
					}
					else
					{
						gLekarz = gLekarz->wsk_nastepny_lekarz;
					}

				}
			}
		}
	}
	gLekarz = gLekarz->wsk_nastepny_lekarz;


}

void wypisz(Lekarz * gLekarz)
{
	while (gLekarz)
	{
		while (gLekarz->head_wizyty)
		{
			cout << gLekarz->head_wizyty->data_wizyty << ";" << gLekarz->head_wizyty->nazwisko_pacjenta << ";" << gLekarz->nazwisko << endl;
			gLekarz->head_wizyty = gLekarz->head_wizyty->wsk_nastepna_wizyta;
		}
		gLekarz = gLekarz->wsk_nastepny_lekarz;
	}
}