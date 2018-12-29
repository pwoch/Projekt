#pragma once

#include <iostream>
#include <string>

using namespace std;


#pragma region Struktury

struct Data
{
	int rok, miesiac, dzien, numer;
};


struct Pacjent
{
	string nazwisko;
	Pacjent * wsk_nastepny_pacjent;
};

struct Wizyta
{
	Data * data_wizyty;
	string nazwisko_pacjenta;
	Pacjent * wsk_pacjent;
	Wizyta * wsk_nastepna_wizyta;
};


struct Lekarz
{
	string nazwisko;
	double œrednia;
	Lekarz * wsk_nastepny_lekarz;
	Wizyta * head_wizyty;
};

#pragma endregion


#pragma region Funkcje

vector <string> pobierz(string);

#pragma endregion


