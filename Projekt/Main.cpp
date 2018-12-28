#include <iostream>
#include <fstream>
#include "Nag³ówek.h"

using namespace std;

int main()
{
	fstream plik;
	plik.open("D:\wizyty.txt");
	if (plik.good())
	{
		string wiersz;
		while (!plik.eof())
		{
			getline(plik, wiersz);
		}
	}
	return 0;
}