#pragma once

#include <iostream>
#include <string>

using namespace std;

struct Wizyta
{
	Data* data_wizyty;
	string nazwisko_pacjenta;
	Pacjent* wsk_pacjent;
	Wizyta* wsk_nastepna_wizyta;
};

struct Data
{
	int rok, miesiac, dzien, numer;
};

struct Lekarz
{
	string nazwisko;
	double œrednia;
	Lekarz* wsk_nastepny_lekarz;
	Wizyta* head_wizyty;
};

struct Pacjent
{
	string nazwisko;
	Pacjent* wsk_nastepny_pacjent;
};
