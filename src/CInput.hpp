/**\file
* @author Rafal Malinowski
* @date 2009.12.07
* @version 0.6
* @class CInput CInput.hpp
* @brief klasa CInput odpowiada za odbieranie sygnalow z myszy i klawiatury
*	
*		
*/
#ifndef CINPUT
#define CINPUT

#include "CMouseObserver.hpp"
#include "CKeyObserver.hpp"
#include <map>
#include "keys.hpp"
#include <cassert>
#include "SDL.h"
#include <iostream>
#include "CSingleton.hpp"
#include "COGLWindow.hpp"
#include "CMouseEvent.hpp"
#include "boost/multi_array.hpp"
#include<fstream>
#include "CLog.hpp"

using namespace std;

class COGLWindow;
class CMouseObserver;
class CKeyObserver;

class CInput : public CSingleton<CInput>
{
	friend class CSingleton<CInput>;

public:


	///metoda dodajaca observatora zainteresowanego akcjami zwiazanymi z mysza
	///@param o referencja do obiektu klasy CMouseObserver (lub po niej dziedziczacego)
	void addMouseObserver(CMouseObserver & o, int Xmin = 0, int Xmax = 0, int Ymin = 0, int Ymax = 0);

	///metoda usuwajaca observatora zainteresowanego akcjami zwiazanymi z mysza
	///@param o referencja do obiektu klasy CMouseObserver (lub po niej dziedziczacego)
	void removeMouseObserver(CMouseObserver & o);

	///metoda dodajaca observatora zainteresowanego akcjami zwiazanymi z klawiatura
	///@param o referencja do obiektu klasy CKeyObserver (lub po niej dziedziczacego)
	void addKeyObserver(CKeyObserver & k);

	///metoda usuwajaca observatora zainteresowanego akcjami zwiazanymi z klawiatura
	///@param o referencja do obiektu klasy CKeyObserver (lub po niej dziedziczacego)
	void removeKeyObserver(CKeyObserver & k);


	/// licznik zliczajacy ilosc observatorow akcji myszy
	static int licznik_obs;

	/// pomocniczna zmienna typu int wykorzystywana w metodzie refreshMove()
	static int pointed_object;

	///metoda mowiaca czy dany klawisz zostal wcisniety
	///@param key kod klawisza o ktorego stan nastepuje pytanie
	///@return true jesli klawisz jest wcisniety i false w przeciwnym wypadku
	bool getKeyState(eKey key);

	///metoda ktora kiedys bedzie zwracac wartosc wspolzednej X myszy
	int getMouseX();
	///metoda ktora kiedys bedzie zwracac wartosc wspolzednej Y myszy
	int getMouseY();
	///metoda ktora przechwytuje zdarzenia z klawiatury i aktualizuje stan klawiszy
	void update();

private:
	///konstruktor domyslny
	CInput();
	///destruktor
	~CInput();
	/// wartosc wspolzedniej X myszy
	int mouseX_;
	/// wartosc wspolzedniej Y myszy
	int mouseY_;
	/// flaga mowiaca czy mysz jest wcisnieta
	bool mouseClicked_;
	/// rozmiar tablicy przechowujacej klawisze
	static const int rozmiar_tablicy = KEY_MENU;
	/// tablica przechowujaca stan wcisniecia wszystkich klawiszy
	char m_Keystates[rozmiar_tablicy];

	void keyAction(SDLKey key, bool keyDown);

	///metoda wywolujace metode refresh we wszystkich observatorach akcji myszy
	void refreshAll();

	///metoda wywolywana gdy poruszy sie myszka, ewentualnie informujaca zainteresowanego ta informacja observatora
	void refreshMove();

	///metoda ktora mowil czy mysz jest wcisnieta
	bool mouseClicked();

	int findMoveObserver();
	/// obiekt klasy CMouseEvent przechowujacy informacje ostatnim zderzeniu zwiazanym z klikaniem
	CMouseEvent MouseEvent;

	/// mapa przechowujaca wszystkich observatorow zainteresowanych obsluga myszki
	map<int, CMouseObserver*> observers_;

	map<int, CKeyObserver*> keyObservers_;

	/// tablica wielowymiarowa przechowujaca informacje o wymiarach observatorow
	boost::multi_array<int, 2> dimensions_;

};

#endif

//~~CInput.hpp