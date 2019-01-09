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

void zamienWizyte(Lekarz * gLekarz,Pacjent * gPacjent, string pacjent, unsigned long data)
{
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
			while (pW)
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
				pW = pL->head_wizyty->wsk_nastepna_wizyta;
			}
			
			pL = pL->wsk_nastepny_lekarz;
		}
		pL = gLekarz;
		data = data + 1;
	}
}

void usunLekarza(Lekarz * gLekarz, Pacjent * gPacjent, string lekarz)
{
	Lekarz * pL1 = gLekarz;
	Lekarz * pL2 = gLekarz;
	Lekarz * pL3 = NULL;
	unsigned long aktualna_data = pobierzCzas();
	while (pL1)
	{
		if (pL1->nazwisko == lekarz)
		{
			Wizyta * pW1 = pL1->head_wizyty;
			while (pW1)
			{
				if (pW1->data_wizyty < aktualna_data)
				{
					usunKonkretnaWizyte(pW1, pW1->nazwisko_pacjenta, pW1->data_wizyty);
				}
				else
				{
					if (pL2->nazwisko == lekarz)
					{
						if (pL2->wsk_nastepny_lekarz == NULL)
						{
							pL2 = gLekarz;
						}
						else {
							pL2 = pL2->wsk_nastepny_lekarz;
						}
						pL3 = pL2;
						while (pL3)
						{
							if (pL2->head_wizyty->data_wizyty != pW1->data_wizyty)
							{
								dodajWizyte(gLekarz, gPacjent, pL3->nazwisko, pW1->data_wizyty, pW1->nazwisko_pacjenta);
								return;
							}
							else
							{
								pW1->data_wizyty += 10;
							}
							pL3 = pL3->wsk_nastepny_lekarz;
						}
					}
					else
					{
						while (pL3)
						{
							if (pL2->head_wizyty->data_wizyty != pW1->data_wizyty)
							{
								dodajWizyte(gLekarz, gPacjent, pL3->nazwisko, pW1->data_wizyty, pW1->nazwisko_pacjenta);
								return;
							}
							else
							{
								pW1->data_wizyty += 10;
							}
							pL3 = pL3->wsk_nastepny_lekarz;
						}
						if (pL2->wsk_nastepny_lekarz == NULL)
						{
							pL2 = gLekarz;
						}
						else
						{
							pL2 = pL2->wsk_nastepny_lekarz;
						}
					}
				}
			}
			pW1 = pW1->wsk_nastepna_wizyta;
		}
		pL1 = pL1->wsk_nastepny_lekarz;
	}
}