#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Nag³ówek.h"
#include <cstdlib>
#include <crtdbg.h>

#define _CRTDBG_MAP_ALLOC
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace std;

int main()
{
	string fin_path = "D:\wizyty.txt";
	fstream fin;
	fin.open(fin_path);
	if (fin.good())
	{
		string wiersz;
		vector<string> wizyta_vec;
		while (!fin.eof())
		{
			getline(fin, wiersz);
			wizyta_vec = pobierz(wiersz);
		}
	}
	fin.close();
	
	system("pause");

	return 0;
}