/** @file */

#pragma once

#include <iostream>
#include <string>

using namespace std;


#pragma region Struktury

/** Element listy pacjentów*/
struct Pacjent
{
	string nazwisko;
	Pacjent * wsk_nastepny_pacjent;
};

/** Element listy wizyt*/
struct Wizyta
{
	unsigned long data_wizyty;
	string nazwisko_pacjenta;
	Pacjent * wsk_pacjent;
	Wizyta * wsk_nastepna_wizyta;
};

/** Element listy lekarzy*/
struct Lekarz
{
	string nazwisko;
	double œrednia;
	Lekarz * wsk_nastepny_lekarz;
	Wizyta * head_wizyty;
};

#pragma endregion


#pragma region Funkcje

/** Pobieranie i rozdzielenie linii tekstu na daty, nazwiska pacjenta, oraz nazwiska lekarza
@param input linia tekstu do wczytania aby rozdzielic go na datê, nazwisko pacjenta oraz nazwisko lekarza
*/
vector <string> pobierz(string input);

/** Sprawdzanie czy instnieje ju¿ taki lekarz
@param gLekarz wskaŸnik na pierwszy element listy lekarzy
@param l_nazwisko nazwisko lekarza do sprawdzenia
*/
bool lekarzIstnieje(Lekarz * gLekarz, string l_nazwisko);

/** Dodawanie lekarza do listy
@param[in, out] gLekarz wskaznik na pierwszy element listy lekarzy, jeœli element zostanie dododany do listy, wskaŸnik bêdzie zmodyfikowany
@param l_nazwisko nazwisko lekarza, który ma byæ dodany do listy
*/
void dodajLekarza(Lekarz * & gLekarz, string l_nazwisko);

/** Sprawdzanie czy instnieje ju¿ taki pacjent
@param gPacjent wskaŸnik na pierwszy element listy pacjentów
@param p_nazwisko nazwisko pacjenta do sprawdzenia
*/
bool pacjentIstnieje(Pacjent * gPacjent, string p_nazwisko);

/** Dodawanie pacjenta do listy
@param[in, out] gPacjent wskaznik na pierwszy element listy pacjentów, jeœli element zostanie dododany do listy, wskaŸnik bêdzie zmodyfikowany
@param p_nazwisko nazwisko pacjenta, który ma byæ dodany do listy
*/
void dodajPacjenta(Pacjent * & gPacjent, string p_nazwisko);

/** Dodawanie wizyty do listy
@param gLekarz wskaŸnik na pierwszy element listy lekarzy
@param gPacjent wskaznik na pierwszy element listy pacjentów
@param p_nazwisko nazwisko lekarza, który ma mieæ dodan¹ wizytê
@param data_wizyty data dodawanej wizyty
@param p_nazwisko nazwisko pacjenta, który ma mieæ dodan¹ wizytê
*/
void dodajWizyte(Lekarz * gLekarz, Pacjent * gPacjent, string l_nazwisko, unsigned long data_wizyty, string p_nazwisko);

/** Pobieranie aktualnej daty*/
unsigned long pobierzCzas();

void wypisz(Lekarz * gLekarz);

/** Usuwanie konkretnej wiyty (wed³ug podanego nazwiska pacjenta i daty wuizyty)
@param[in, out] head wskaŸnik na pierwszy element listy wizyt
@param pacjent nazwisko pacjenta którego wizyta ma byæ usuniêta
@param data data wizyty do usuniêcia
*/
void usunKonkretnaWizyte(Wizyta * & head, string pacjent, unsigned long data);

/** Usuwanie konkretnego lekarza (wed³ug podanego nazwiska lekarza)
@param[in, out] head wskaŸnik na pierwszy element listy lekarzy
@param lekarz nazwisko lekarza który ma byæ usuniêty
*/
void usunKonkretnegoLekarza(Lekarz *& head, string lekarz);

/** Usuwanie listy wizyt
@param[in, out] head wskaznik na pierwszy element listy wizyt do usuniêcia
*/
void usunListeWizyt(Wizyta * & head);

/** Zanienianie wizyty pacjenta (usuwanie podanej wizyty i znalezienie najblizszego wolnego terminu oraz utworzenie nowej wizyty w tym terminie)
@param gLekarz gLekarz wskaŸnik na pierwszy element listy lekarzy
@param gPacjent wskaznik na pierwszy element listy pacjentów
@param pacjent nazwisko pacjenta którego wizyta ma byæ zamieniona
@param data data wizyty do zamienienia 
*/
void zamienWizyte(Lekarz * gLekarz, Pacjent * gPacjent, string pacjent, unsigned long data);

void przeniesWizytyLekarza(Lekarz * gLekarz, Pacjent * gPacjent, string lekarz);

void usunLekarza(Lekarz *& gLekarz, Pacjent * gPacjent, string lekarz);

void liczSrednie(Lekarz * gLekarz);

int obetnijDoRoku(unsigned long data);

int obetnijDoMiesiaca(unsigned long data);

#pragma endregion


