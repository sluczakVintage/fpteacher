/**
* @author Rafal Malinowski
* @date 2009.12.07
* @version 0.1_draft
* @brief klasa CInput odpowiada za odbieranie sygna³ów z myszy i klawiatury
*	
*		
*/
#ifndef CINPUT
#define CINPUT

#include "CMouseObserver.hpp"
#include <map>
#include "keys.hpp"
#include <cassert>
#include "SDL.h"
#include <iostream>
#include "CSingleton.hpp"
#include "COGLWindow.hpp"
//#include "CGui.hpp"

using namespace std;

class COGLWindow;
class CMouseObserver;

class CInput : public CSingleton<CInput>
{
	friend CSingleton<CInput>;

public:

	void addMouseObserver(CMouseObserver & o);
	void removeMouseObserver(CMouseObserver & o);
	void refreshAll();

	static int licznik_obs;
	///metoda mowiaca czy dany klawisz zostal wcisniety
	///@param key kod klawisza o ktorego stan nastepuje pytanie
	///@return true jesli klawisz jest wcisniety i false w przeciwnym wypadku
	bool getKeyState(eKey key);

	///metoda ktora kiedys bedzie zwracac wartosc wspolzednej X myszy
	int getMouseX();
	///metoda ktora kiedys bedzie zwracac wartosc wspolzednej Y myszy
	int getMouseY();
	///metoda ktora mowil czy mysz jest wcisnieta
	bool mouseClicked();
	///metoda ktora przechwytuje zdarzenia z klawiatury i aktualizuje stan klawiszy
	void update();

private:
	///konstruktor domyslny
	CInput();
	///destruktor domyslny
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


	map<int, CMouseObserver*> observers_;

};

#endif
