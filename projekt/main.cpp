#include <cstring>

#include "funkcje.h"


int main(int argc, char *argv[])
{
	std::string plik_tras;
	std::string plik_zadania;
	std::string plik_wyniku;

	bool d = 0, t = 0, o = 0;

	if (argc == 7)
	{
		for (int i = 1; i < argc; i++)
		{
			if (strcmp(argv[i], "-d") == 0)
			{
				plik_tras = argv[i + 1];
				d = true;
			}
			else if (strcmp(argv[i], "-t") == 0)
			{
				plik_zadania = argv[i + 1];
				t = true;
			}
			else if (strcmp(argv[i], "-o") == 0)
			{
				plik_wyniku = argv[i + 1];
				o = true;
			}
		}
		if (d * t * o == false)
		{
			std::cout << "Blad: Brakuje niektorych przelacznikow, powinnny one wygladac tak: " << std::endl;
			std::cout << "-d plik wejsciowy z drogami" << std::endl << "-t plik wejsciowy z trasami" << std::endl << "-o plik wyjsciowy z wynikiem";
			return 0;
		}
		else
		{
			std::cout << "Program zostal uruchomiony"<<std::endl;
			czytaj(plik_tras, plik_zadania, plik_wyniku);
		}
	}
	else
	{
		std::cout << "Blad: Bledne przelaczniki, powinny one wygladac tak: " << std::endl;
		std::cout << "-d plik wejsciowy z drogami" << std::endl << "-t plik wejsciowy z trasami" << std::endl << "-o plik wyjsciowy z wynikiem";
		return 0;
	}
}
