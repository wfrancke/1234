#ifndef FUNKCJE_H
#define FUNKCJE_H

#include <string>
#include <iostream>
#include <fstream>

struct miasto;

/**  Lista podwieszana do miast przechowuj¹ca potencjalne po³¹czenia z danego wierzcho³ka oraz ich d³ugoœci.
*/

struct cele
{
	miasto* wierzcholek;
	cele* next;
	int odleglosc;
};

/**  Lista dwukierunkowa przechowuj¹ca wszystkie miasta (wierzcho³ki) oraz dane zwracane przez kolejkê,
     czyli miasto poprzednie na najktrótszej drodze oraz odleg³oœæ od miasta Ÿród³owego (wagê danego wierzcho³ka grafu).
	 Je¿eli miasto nie ma poprzednika/waga jest nieskoñczona, to znaczy ¿e nie prowadzi do niego ¿adna droga.
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

/**  Struktura listy dwukierunkowej odpowiedzialnej za dzia³anie kolejki u¿ywanej w algorytmie dijkstry,
     usuwana na koñcu dzia³ania owego algorytmu
*/

struct kolejka
{
	miasto* miasto;
	kolejka* next;
	kolejka* prev;
};

/**  G³ówna Funkcja odczytuj¹ca dane wejœciowe.
     @param plik_tras Plik z trasami
	 @param plik_zadania Plik z tras¹ do wyznaczenia
	 @param plik_wyniku Plik zwrotny z najkrótsz¹ drog¹
*/

void czytaj(std::string plik_tras, std::string plik_zadania, std::string plik_wyniku);

/**  Funkcja dodaj¹ca miasto (wierzcho³ek).
     @param pHead WskaŸnik na pierwszy element w liœcie
	 @param lokacja Miasto pocz¹tkowe
	 @param destynacja Miasto docelowe
	 @param odleglosc Odleg³oœæ dziel¹ca ww. miasta
*/

void dodaj_miasto(miasto*& pHead, std::string lokacja, std::string destynacja, int odleglosc);

/**  Funkcja dodaj¹ca cel do miasta.
     @param m1 WskaŸnik na miasto
	 @param m2 WskaŸnik na cel
	 @param odleglosc Odleg³oœæ dziel¹ca miasto i cel
*/

void dodaj_cel(miasto*& m1, miasto*& m2, int odleglosc);

/**  Funkcja sprawdzaj¹ca czy dany wierzcho³ek ju¿ istnieje na liœcie.
     @param pHead WskaŸnik na pierwszy element w liœcie
	 @param nazwa Nazwa sprawdzanego miasta
	 @return W przypadku znalezienia miasta zwraca jego wskaŸnik, w przeciwnym wypadku zwraca nullptr.
*/

miasto* sprawdz(miasto* pHead, std::string nazwa);

/**  Funkcja usuwaj¹ca miasto z listy.
     @param pHead WskaŸnik na pierwszy element w liœcie
*/

void usun_miasto(miasto* pHead);

/**  Funkcja usuwaj¹ca cel z listy.
     @param pHead WskaŸnik na pierwszy element w liœcie
*/

void usun_cel(cele* pHead);

/**  Funkcja pomocnicza tworz¹ca wskaŸnik na poprzednika w liœcie.
     @param pHead WskaŸnik na pierwszy element w liœcie
*/

void rob_prev(miasto* pHead);

/**  Funkcja pomocnicza tworz¹ca wskaŸnik na poprzednika w kolejce.
     @param pHead WskaŸnik na pierwszy element w kolejce
*/

void rob_prev_k(kolejka* pHead);

/**  Funkcja odpowiadaj¹ca za wykonanie algorytmu dijkstry - wyznaczenie najkrótszej trasy z danego Ÿród³a do ka¿dego wierzcho³ka
     @param pHead WskaŸnik na pierwszy element w liœcie
	 @param lokacja Nazwa miasto Ÿród³owego
*/

void dijkstra(miasto* pHead, std::string lokacja);

/**  Funkcja odpowiadaj¹ca za wypisywanie trasy
     @param lokacja Nazwa miasta Ÿród³owego
	 @param destynacja Nazwa miasta do którego trase mamy wyznaczyæ
	 @param wynik strumieñ pliku wyjœciowego
	 @param pHead WskaŸnik na pierwszy element w liœcie
*/

void zapisz(std::string lokacja, std::string destynacja, std::ofstream& wynik, miasto* pHead);

#endif
