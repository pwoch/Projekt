#include <iostream>
#include <fstream>
#include "Nag��wek.h"

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