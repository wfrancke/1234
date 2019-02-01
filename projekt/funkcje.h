#ifndef FUNKCJE_H
#define FUNKCJE_H

#include <string>
#include <iostream>
#include <fstream>

struct miasto;

/**  Lista podwieszana do miast przechowuj�ca potencjalne po��czenia z danego wierzcho�ka oraz ich d�ugo�ci.
*/

struct cele
{
	miasto* wierzcholek;
	cele* next;
	int odleglosc;
};

/**  Lista dwukierunkowa przechowuj�ca wszystkie miasta (wierzcho�ki) oraz dane zwracane przez kolejk�,
     czyli miasto poprzednie na najktr�tszej drodze oraz odleg�o�� od miasta �r�d�owego (wag� danego wierzcho�ka grafu).
	 Je�eli miasto nie ma poprzednika/waga jest niesko�czona, to znaczy �e nie prowadzi do niego �adna droga.
*/

struct miasto
{
	std::string nazwa;
	miasto* next;
	miasto* prev;
	cele* cel;

	miasto* poprzednik;
	int waga;
};

/**  Struktura listy dwukierunkowej odpowiedzialnej za dzia�anie kolejki u�ywanej w algorytmie dijkstry,
     usuwana na ko�cu dzia�ania owego algorytmu
*/

struct kolejka
{
	miasto* miasto;
	kolejka* next;
	kolejka* prev;
};

/**  G��wna Funkcja odczytuj�ca dane wej�ciowe.
     @param plik_tras Plik z trasami
	 @param plik_zadania Plik z tras� do wyznaczenia
	 @param plik_wyniku Plik zwrotny z najkr�tsz� drog�
*/

void czytaj(std::string plik_tras, std::string plik_zadania, std::string plik_wyniku);

/**  Funkcja dodaj�ca miasto (wierzcho�ek).
     @param pHead Wska�nik na pierwszy element w li�cie
	 @param lokacja Miasto pocz�tkowe
	 @param destynacja Miasto docelowe
	 @param odleglosc Odleg�o�� dziel�ca ww. miasta
*/

void dodaj_miasto(miasto*& pHead, std::string lokacja, std::string destynacja, int odleglosc);

/**  Funkcja dodaj�ca cel do miasta.
     @param m1 Wska�nik na miasto
	 @param m2 Wska�nik na cel
	 @param odleglosc Odleg�o�� dziel�ca miasto i cel
*/

void dodaj_cel(miasto*& m1, miasto*& m2, int odleglosc);

/**  Funkcja sprawdzaj�ca czy dany wierzcho�ek ju� istnieje na li�cie.
     @param pHead Wska�nik na pierwszy element w li�cie
	 @param nazwa Nazwa sprawdzanego miasta
	 @return W przypadku znalezienia miasta zwraca jego wska�nik, w przeciwnym wypadku zwraca nullptr.
*/

miasto* sprawdz(miasto* pHead, std::string nazwa);

/**  Funkcja usuwaj�ca miasto z listy.
     @param pHead Wska�nik na pierwszy element w li�cie
*/

void usun_miasto(miasto* pHead);

/**  Funkcja usuwaj�ca cel z listy.
     @param pHead Wska�nik na pierwszy element w li�cie
*/

void usun_cel(cele* pHead);

/**  Funkcja pomocnicza tworz�ca wska�nik na poprzednika w li�cie.
     @param pHead Wska�nik na pierwszy element w li�cie
*/

void rob_prev(miasto* pHead);

/**  Funkcja pomocnicza tworz�ca wska�nik na poprzednika w kolejce.
     @param pHead Wska�nik na pierwszy element w kolejce
*/

void rob_prev_k(kolejka* pHead);

/**  Funkcja odpowiadaj�ca za wykonanie algorytmu dijkstry - wyznaczenie najkr�tszej trasy z danego �r�d�a do ka�dego wierzcho�ka
     @param pHead Wska�nik na pierwszy element w li�cie
	 @param lokacja Nazwa miasto �r�d�owego
*/

void dijkstra(miasto* pHead, std::string lokacja);

/**  Funkcja odpowiadaj�ca za wypisywanie trasy
     @param lokacja Nazwa miasta �r�d�owego
	 @param destynacja Nazwa miasta do kt�rego trase mamy wyznaczy�
	 @param wynik strumie� pliku wyj�ciowego
	 @param pHead Wska�nik na pierwszy element w li�cie
*/

void zapisz(std::string lokacja, std::string destynacja, std::ofstream& wynik, miasto* pHead);

#endif
