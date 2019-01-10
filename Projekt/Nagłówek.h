#pragma once

#include <iostream>
#include <string>

using namespace std;


#pragma region Struktury

struct Pacjent
{
	string nazwisko;
	Pacjent * wsk_nastepny_pacjent;
};

struct Wizyta
{
	unsigned long data_wizyty;
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

bool lekarzIstnieje(Lekarz *, string);

void dodajLekarza(Lekarz * &, string);

bool pacjentIstnieje(Pacjent *, string);

void dodajPacjenta(Pacjent * & , string);

void dodajWizyte(Lekarz * , Pacjent * , string , unsigned long , string);

void wypisz(Lekarz *);

void usunKonkretnaWizyte(Wizyta * & , string , unsigned long);

void usunKonkretnegoLekarza(Lekarz *& , string );

void usunListeWizyt(Wizyta * & );

void zamienWizyte(Lekarz * , Pacjent * , string , unsigned long);

void usunLekarza(Lekarz * , Pacjent * , string);

void usunLekarza(Lekarz * gLekarz, Pacjent * gPacjent, string lekarz);

#pragma endregion


