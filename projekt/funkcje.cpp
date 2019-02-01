#include <iostream>
#include <fstream>
#include <string>

#include "funkcje.h"

void czytaj(std::string plik_tras, std::string plik_zadania, std::string plik_wyniku)
{
	std::ifstream trasy(plik_tras);
	std::ifstream zadanie(plik_zadania);
	std::ofstream wynik(plik_wyniku, std::ofstream::out | std::ofstream::app);

	std::string miasto_pocz, miasto_konc, lokacja, destynacja;
	int odleglosc;
	int inf = 2147483647;
	miasto* pHead = nullptr;

	if (trasy)
	{
		while (trasy >> miasto_pocz >> miasto_konc >> odleglosc)                           // ODCZYTUJEMY TRASY
		{
			if (miasto_pocz != miasto_konc)
				dodaj_miasto(pHead, miasto_pocz, miasto_konc, odleglosc);                  // DODAJEMY WIERZCHOLKI
		}
		rob_prev(pHead);
		if (zadanie)
		{
			while (zadanie >> lokacja >> destynacja)                                      // ODCZYTUJEMY ZADANIE
			{
				if (!sprawdz(pHead, lokacja) && !sprawdz(pHead, destynacja))              // SPRAWDZAMY CZY ZADANE MIASTA ISTNIEJA
					wynik << std::endl << "trasa: " << lokacja << " -> " << destynacja << " ( - km): " << std::endl << "   PODANA LOKACJA/CEL NIE ISTNIEJE" << std::endl;
				else
				{
					if (lokacja == destynacja)                                            // SPRAWDZAMY CZY LOKACJA JEST ROZNA OD DESTYNACJI
						wynik << std::endl << "trasa: " << lokacja << " --> " << destynacja << " ( - km): " << std::endl << "   PODANY CEL JEST TAKI SAM JAK LOKACJA" << std::endl;
					else
					{
						dijkstra(pHead, lokacja);                                         // WYKONUJEMY OBLICZENIE NAJKROTSZYCH DROG
						miasto* pom = pHead;
						while (pom->nazwa != destynacja)                                  // SPRAWDZAMY CZY DROGA DO CELU ISTNIEJE
						{
							pom = pom->next;
						}
						if (pom->waga == inf || pom->waga < 0)
							wynik << std::endl << "trasa: " << lokacja << " -> " << destynacja << " ( - km): " << std::endl << "   BRAK POLACZENIA MIEDZY MIASTAMI" << std::endl << std::endl;
						else
							zapisz(lokacja, destynacja, wynik, pHead);                    // WYPISUJEMY DO PLIKU
					}
				}
			}
		}
		else std::cout << "Plik zadania nie zostal znaleziony";
		usun_miasto(pHead);
	}
	else std::cout << "Plik tras nie zostal znaleziony";
}

void dodaj_miasto(miasto*& pHead, std::string lokacja, std::string destynacja, int odleglosc)
{
	miasto* m1 = nullptr;
	miasto* m2 = nullptr;
	miasto* sprawdzenie = sprawdz(pHead, lokacja);

	if (pHead == nullptr || sprawdzenie == nullptr)
	{
		pHead = new miasto{ lokacja, pHead, nullptr, nullptr };
		m1 = pHead;
	}
	else m1 = sprawdzenie;
	sprawdzenie = sprawdz(pHead, destynacja);
	if (pHead == nullptr || sprawdzenie == nullptr)
	{
		pHead = new miasto{ destynacja, pHead, nullptr, nullptr };
		m2 = pHead;
	}
	else m2 = sprawdzenie;
	dodaj_cel(m1, m2, odleglosc);
}

void dodaj_cel(miasto*& m1, miasto*& m2, int odleglosc)
{
	m1->cel = new cele{ m2, m1->cel, odleglosc };
}

miasto* sprawdz(miasto* pHead, std::string nazwa)
{
	while (pHead)
	{
		if (pHead->nazwa == nazwa) return pHead;
		pHead = pHead->next;
	}
	return nullptr;
}

void usun_miasto(miasto* pHead)
{
	while (pHead)
	{
		miasto* next = pHead->next;
		usun_cel(pHead->cel);
		delete pHead;
		pHead = next;
	}

}

void usun_cel(cele* pHead)
{
	if (pHead)
	{
		usun_cel(pHead->next);
		delete pHead;
		pHead = nullptr;
	}
}

void rob_prev(miasto* pHead)
{
	miasto* pom = nullptr;
	while (pHead->next)
	{
		pom = pHead->next;
		pom->prev = pHead;
		pHead = pHead->next;
	}
}

void dijkstra(miasto* pHead, std::string lokacja)
{
	int inf = 2147483647;
	kolejka* pKolejka = nullptr;
	miasto* pMiasto = pHead;
	while (pMiasto->next)
	{
		pMiasto = pMiasto->next;
	}
	while (pMiasto)
	{
		if (pMiasto->nazwa == lokacja)
		{
			pKolejka = new kolejka{ pMiasto, pKolejka, nullptr };
			pMiasto->waga = 0;
		}
		else
		{
			pKolejka = new kolejka{ pMiasto, pKolejka, nullptr };
			pMiasto->waga = inf;
		}
		if (pMiasto->prev)
			pMiasto = pMiasto->prev;
		else break;
	}

	rob_prev_k(pKolejka);

	//////////////

	while (pKolejka)                                              // Dopoki kolejka jest pelna                         
	{
		while (pKolejka->prev)                                    // ustwiamy pKolejka na poczatek
		{
			pKolejka = pKolejka->prev;
		}

		kolejka* najblizszy = pKolejka;                           // Szukamy wierzcholka o najmniejszym priorytecie (wadze)
		while (pKolejka)
		{
			if (pKolejka->wierzch->waga < najblizszy->wierzch->waga)
				najblizszy = pKolejka;
			if (pKolejka->next)
				pKolejka = pKolejka->next;
			else break;
		}
		pKolejka = najblizszy;                                    // Ustawiamy pTablica na wierzcholek o najmniejszym priorytecie
		if (pKolejka->wierzch->waga != inf)
		{
			cele* pCel = pKolejka->wierzch->cel;
			while (pCel)                                              // Sprawdzamy wszystkie mozliwe sciezki
			{
				if (pKolejka->wierzch->waga + pCel->odleglosc < pCel->wierzcholek->waga)
				{
					pCel->wierzcholek->waga = pCel->odleglosc + pKolejka->wierzch->waga;
					pCel->wierzcholek->poprzednik = pKolejka->wierzch;
				}
				pCel = pCel->next;
			}
		}

		//wypisz

		kolejka* nastepny = pKolejka->next;
		kolejka* poprzedni = pKolejka->prev;

		delete pKolejka;                                          // Usuwamy wierzcholek o najmniejszym priorytecie

		if (poprzedni) poprzedni->next = nastepny;                 // Poprawiamy wskazniki
		if (nastepny) nastepny->prev = poprzedni;

		if (nastepny)pKolejka = nastepny;
		else pKolejka = poprzedni;
	}
}

void rob_prev_k(kolejka* pHead)
{
	kolejka* pom = nullptr;
	while (pHead->next)
	{
		pom = pHead->next;
		pom->prev = pHead;
		pHead = pHead->next;
	}
}

void zapisz(std::string lokacja, std::string destynacja, std::ofstream& wynik, miasto* pHead)
{
	miasto* pCel = pHead;
	while (pCel->nazwa != destynacja)
	{
		pCel = pCel->next;
	}
	wynik << "trasa: " << lokacja << " --> " << destynacja << " (" << pCel->waga << " km):" << std::endl;
	while (pCel->poprzednik)
	{
		wynik << " ^ " << pCel->poprzednik->nazwa << " --> " << pCel->nazwa << "  " << pCel->waga - pCel->poprzednik->waga << std::endl;
		pCel = pCel->poprzednik;
	}
	while (pHead)
	{
		pHead->poprzednik = nullptr;
		pHead = pHead->next;
	}
}