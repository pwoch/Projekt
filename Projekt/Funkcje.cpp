/** @file */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>
#include <winbase.h>
#include <climits>
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
	gLekarz = new Lekarz{ l_nazwisko,0, gLekarz, NULL};
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
			bool dataZajeta = false;
			Wizyta * pWizyta = gLekarz->head_wizyty;
			while (pWizyta)
			{
				if (pWizyta->data_wizyty == data_wizyty)
				{
					dataZajeta = true;
					break;
				}
				pWizyta = pWizyta->wsk_nastepna_wizyta;
			}
			string data_string = to_string(data_wizyty);
			int dziesiatki = (int)(data_string[8] - '0');
			int jednosci = (int)(data_string[9] - '0');
			int id_wizyty = 10 * dziesiatki + jednosci;

			if (id_wizyty > 0 && id_wizyty <= 10 && !dataZajeta)
			{
				gLekarz->head_wizyty = new Wizyta{ data_wizyty,p_nazwisko,tmpPacjent,gLekarz->head_wizyty };
			}
			return;
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

void wypisz(Lekarz * gLekarz)
{
	Lekarz * pL = gLekarz;
	while (pL)
	{
		Wizyta * pW = pL->head_wizyty;
		while (pW)
		{
			cout << pW->data_wizyty << ";" << pW->nazwisko_pacjenta << ";" << pL->nazwisko << endl;
			pW = pW->wsk_nastepna_wizyta;
		}
		cout << "Srednia wizyt dla lekarza " << pL->nazwisko << ": " << pL->œrednia << endl;
		pL = pL->wsk_nastepny_lekarz;
	}
}

void usunKonkretnaWizyte(Wizyta * & head, string pacjent,unsigned long data)
{
	Wizyta * p, *pop;

	pop = NULL;

	for (p = head; p != NULL; pop = p, p = p->wsk_nastepna_wizyta)
	{
		if (p->data_wizyty == data and p->nazwisko_pacjenta == pacjent)
		{ 
			if (pop == NULL)
			{
				head = p->wsk_nastepna_wizyta;
			}
			else
			{
				pop->wsk_nastepna_wizyta = p->wsk_nastepna_wizyta;
			}

			delete p;

			return;
		}
	}
}

void usunKonkretnegoLekarza(Lekarz *& head, string lekarz)
{
	Lekarz *curr, *prev;

	prev = NULL;

	for (curr = head; curr != NULL; prev = curr, curr = curr->wsk_nastepny_lekarz)
	{

		if (curr->nazwisko == lekarz)
		{
			if (prev == NULL)
			{
				head = curr->wsk_nastepny_lekarz;
			}
			else
			{
				prev->wsk_nastepny_lekarz = curr->wsk_nastepny_lekarz;
			}

			delete curr;

			return;
		}
	}
	
}

void usunListeWizyt(Lekarz * gLekarz, string lekarz)
{
	Lekarz * pL = gLekarz;
	Lekarz * usuwanyL = NULL;
	while (pL)
	{
		if (pL->nazwisko == lekarz)
		{
			usuwanyL = pL;
			break;
		}
		pL = pL->wsk_nastepny_lekarz;
	}
	Wizyta * & head = pL->head_wizyty;
	while (head)
	{
		Wizyta * p = head->wsk_nastepna_wizyta;
		delete head;
		head = p;
	}
}

void zamienWizyte(Lekarz * gLekarz,Pacjent * gPacjent, string pacjent, unsigned long data)
{
	if (!pacjentIstnieje(gPacjent, pacjent))
	{
		cout << "Pacjent " << pacjent << " nie istnieje" << endl;
		return;
	}
	Lekarz * pL = gLekarz;
	
	bool wizyta_przepisana = false;
	while (pL)
	{
		usunKonkretnaWizyte(pL->head_wizyty, pacjent, data);
		pL = pL->wsk_nastepny_lekarz;
	}
	pL = gLekarz;
	string tmp_data = to_string(data);
	tmp_data[8] = '0';
	tmp_data[9] = '0';
	data = stoul(tmp_data);
	data += 101;
	while (wizyta_przepisana == false)
	{
		while (pL)
		{
			bool data_wystapila = false;
			bool koniec_wizyt = false;
			Wizyta * pW = pL->head_wizyty;
			while (pW)						//petla nieskonczona
			{
				if (pW->data_wizyty == data)
				{
					data_wystapila = true;
				}
				if (pW->wsk_nastepna_wizyta == NULL)
				{
					koniec_wizyt = true;
				}
				if (!data_wystapila and koniec_wizyt)
				{
					dodajWizyte(gLekarz, gPacjent, pL->nazwisko, data, pacjent);
					wizyta_przepisana = true;
					return;
				}
				//pW = pL->head_wizyty->wsk_nastepna_wizyta;
				pW = pW->wsk_nastepna_wizyta;
			}
			
			pL = pL->wsk_nastepny_lekarz;
		}
		pL = gLekarz;
		data = data + 1;
	}
}

void przeniesWizytyLekarza(Lekarz * gLekarz, Pacjent * gPacjent, string lekarz)
{
	if (!lekarzIstnieje(gLekarz, lekarz)) 
	{
		cout << "Podany lekarz: " << lekarz << " nie istnieje" << endl;
		return;
	}
	Lekarz * pL = gLekarz;
	Lekarz * usuwanyL = NULL;
	while (pL)
	{
		if (pL->nazwisko == lekarz)
		{
			usuwanyL = pL;
			break; 
		}
		pL = pL->wsk_nastepny_lekarz;
	}
	pL = gLekarz;
	Wizyta * pW = usuwanyL->head_wizyty;
	while (pW)		//nie rozdziela równomiernie
	{
		if(pL->nazwisko==lekarz)
		{
			if (pL->wsk_nastepny_lekarz == NULL)
			{
				pL = gLekarz;
			}
			else
			{
				pL = pL->wsk_nastepny_lekarz;
			}
		}
		bool wizyta_przepisana = false;
		while (wizyta_przepisana == false)
		{
			bool data_wystapila = false;
			bool koniec_wizyt = false;
			Wizyta * pwiz = pL->head_wizyty;
			while (pwiz)
			{
				if (pwiz->data_wizyty == pW->data_wizyty)
				{
					data_wystapila = true;
				}
				if (pwiz->wsk_nastepna_wizyta == NULL)
				{
					koniec_wizyt = true;
				}
				if (!data_wystapila && koniec_wizyt)
				{
					dodajWizyte(gLekarz, gPacjent, pL->nazwisko, pW->data_wizyty, pW->nazwisko_pacjenta);
					wizyta_przepisana = true;
					break;
				}
				if(data_wystapila && koniec_wizyt)
				{
					pW->data_wizyty = pW->data_wizyty + 1;
				}
				pwiz = pwiz->wsk_nastepna_wizyta;
			}
		}
		if (pL->wsk_nastepny_lekarz == NULL)
		{
			pL = gLekarz;
		}
		else
		{
			pL = pL->wsk_nastepny_lekarz;
		}
		pW = pW->wsk_nastepna_wizyta;
	}
}

void usunLekarza(Lekarz *& gLekarz, Pacjent * gPacjent, string lekarz)
{
	if (lekarzIstnieje(gLekarz, lekarz))
	{
		przeniesWizytyLekarza(gLekarz, gPacjent, lekarz);
		usunListeWizyt(gLekarz, lekarz);
		usunKonkretnegoLekarza(gLekarz, lekarz);
	}
	else
	{
		cout << "Lekarz " << lekarz << " nie istnieje" <<endl;
	}
}

void liczSrednie(Lekarz * gLekarz) 
{
	while (gLekarz)
	{
		unsigned long max = 0;
		unsigned long min = ULONG_MAX;
		int iterator = 0;
		Wizyta * gWizyta = gLekarz->head_wizyty;

		while (gWizyta)
		{
			int currentDate = gWizyta->data_wizyty;
			if(currentDate < min)
			{
				min = currentDate;
			}
			if (currentDate > max) 
			{
				max = currentDate;
			}
			++iterator;
			gWizyta = gWizyta->wsk_nastepna_wizyta;
		}

		double srednia = 0;

		if (min != ULONG_MAX && max != 0)
		{
			int rok_min = pobierzRok(min);
			int rok_max = pobierzRok(max);
			int miesiac_min = pobierzMiesiac(min);
			int miesiac_max = pobierzMiesiac(max);

			int mianownik = (miesiac_max - miesiac_min + 1 + (rok_max - rok_min) * 12);
			if (mianownik != 0)
			{
				srednia = iterator / mianownik;
			}
		}
		
		gLekarz->œrednia = srednia;
		gLekarz = gLekarz->wsk_nastepny_lekarz;
	}
}

int pobierzRok(unsigned long data) 
{
	string tmp_data = to_string(data);
	string newData = to_string(tmp_data[0]) + to_string(tmp_data[1]) + to_string(tmp_data[2]) + to_string(tmp_data[3]);
	int year = stoi(newData);
	return year;
}

int pobierzMiesiac(unsigned long data) 
{
	string tmp_data = to_string(data);
	string newData = to_string(tmp_data[4]) + to_string(tmp_data[5]);
	int month = stoi(newData);
	return month;
}
