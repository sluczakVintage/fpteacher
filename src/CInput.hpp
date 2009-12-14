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

#include "keys.hpp"
#include <cassert>
#include "SDL.h"
#include <iostream>
#include "CSingleton.hpp"

using namespace std;
 

class CInput : public CSingleton<CInput>
{
	friend CSingleton<CInput>;

public:

	///metoda mowiaca czy dany klawisz zostal wcisniety
	///@param key kod klawisza o ktorego stan nastepuje pytanie
	///@return true jesli klawisz jest wcisniety i false w przeciwnym wypadku
	bool getKeyState(eKey key);

	///metoda ktora kiedys bedzie zwracac wartosc wspolzednej X myszy
	int getMouseX();
	///metoda ktora kiedys bedzie zwracac wartosc wspolzednej Y myszy
	int getMouseY();

	///metoda ktora kiedys bedzie mowila czy mysz jest wcisnieta
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
	/// tablica przechowujaca stan wcisniecia wszystkich klawiszy
	char m_Keystates[200];


};

#endif