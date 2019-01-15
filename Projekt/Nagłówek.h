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

/** Sprawdzanie czy instnieje ju¿ taka wizyta
@param gLekarz wskaŸnik na pierwszy element listy lekarzy
@param pacjent nazwisko pacjenta do sprawdzenia
@param data data wizyty do sprawdzenia
*/

bool wizytaIstnieje(Lekarz * gLekarz, string pacjent, unsigned long data);

/** Pobieranie aktualnej daty*/
unsigned long pobierzCzas();

void wypisz(Lekarz * gLekarz);

/** Usuwanie konkretnej wiyty (wed³ug podanego nazwiska pacjenta i daty wuizyty)
@param[in, out] head wskaŸnik na pierwszy element listy wizyt, jeœli element zostanie usuniety z listy, wskaŸnik bêdzie zmodyfikowany
@param pacjent nazwisko pacjenta którego wizyta ma byæ usuniêta
@param data data wizyty do usuniêcia
*/
void usunKonkretnaWizyte(Wizyta * & head, string pacjent, unsigned long data);

/** Usuwanie konkretnego lekarza (wed³ug podanego nazwiska lekarza)
@param[in, out] head wskaŸnik na pierwszy element listy lekarzy, jeœli element zostanie usuniety z listy, wskaŸnik bêdzie zmodyfikowany
@param lekarz nazwisko lekarza który ma byæ usuniêty
*/
void usunKonkretnegoLekarza(Lekarz *& head, string lekarz);

/** Usuwanie listy wizyt
@param[in, out] head wskaznik na pierwszy element listy wizyt do usuniêcia, jeœli element zostanie usuniety z listy, wskaŸnik bêdzie zmodyfikowany
*/
void usunListeWizyt(Wizyta * & head);

/** Zanienianie wizyty pacjenta (usuwanie podanej wizyty i znalezienie najblizszego wolnego terminu oraz utworzenie nowej wizyty w tym terminie)
@param gLekarz gLekarz wskaŸnik na pierwszy element listy lekarzy
@param gPacjent wskaznik na pierwszy element listy pacjentów
@param pacjent nazwisko pacjenta którego wizyta ma byæ zamieniona
@param data data wizyty do zamienienia 
*/
void zamienWizyte(Lekarz * gLekarz, Pacjent * gPacjent, string pacjent, unsigned long data);

/** Przenoszenie wizyt lekarza (równomierne przeniesienie wizyt lekarza na innych lekarzy)
@param gLekarz gLekarz wskaŸnik na pierwszy element listy lekarzy
@param gPacjent wskaznik na pierwszy element listy pacjentów
@param lekarz nazwisko lekarza krtórego wizyty maj¹ byæ przeniesione
*/
void przeniesWizytyLekarza(Lekarz * gLekarz, Pacjent * gPacjent, string lekarz);

/** Usuwanie lekarza i rozdziela jego wizyty równomiernie na innych lekarzy
@param[in, out] gLekarz wskaznik na pierwszy element listy lekarzy, jeœli element zostanie usuniety z listy, wskaŸnik bêdzie zmodyfikowany
@param gPacjent wskaznik na pierwszy element listy pacjentów
@param lekarz nazwisko lekarza krtórego wizyty maj¹ byæ przeniesione
*/ 
void usunLekarza(Lekarz *& gLekarz, Pacjent * gPacjent, string lekarz);

/** Liczenie œredniej liczby przyjêæ lekarza na miesi¹c
@param gLekarz wskaŸnik na pierwszy element listy lekarzy
*/
void liczSrednie(Lekarz * gLekarz);

/** Pobieranie roku z pe³nej daty
@param data pe³na data
*/
int pobierzRok(unsigned long data);

/** Pobieranie miesiaca z pe³nej daty
@param data pe³na data
*/
int pobierzMiesiac(unsigned long data);

#pragma endregion


