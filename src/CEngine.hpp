/**
* @author Rafal Malinowski
* @date 2009.12.07
* @version 0.1_draft
* @brief klasa ENgine odpowiada za poprawne dzia³anie silnika gry
*	
*		
*/
#ifndef CENGINE
#define CENGINE

#include <cassert>
#include "SDL.h"
#include <iostream>
#include "CSingleton.hpp"
#include "COGLWindow.hpp"
#include "CInput.hpp"
#include "CWorld.hpp"
#include "CTimer.hpp"
#include "CTimerObserver.hpp"
#include "CEntity.hpp"
#include "CStaticEntity.hpp"

using namespace std;

class CEngine : public CSingleton<CEngine>, public CTimerObserver
{
	friend CSingleton<CEngine>;
public:

	///metoda w ktorej odpalany jest sdl, oraz uruchamiane sa konstruktory wielu klas (COGLWindow, CInput itd...)
	bool init();
	///metoda posiadajaca glowna petle programu
	void start();
	///metoda odpowiedzialna za zamykanie SDLa oraz ewentualne aktywowanie destruktorow roznych klas
	void end();

private:
	///konstruktor domyslny
	CEngine();
	///destruktor domyslny
	~CEngine();	

	/// flaga ktora przyjmuje wartosc true jesli ma byc robiony refresh przy pomocy obserwatora i wartosc false w przeciwnej sytuacji
	bool refresh_flag;
	
	/// metoda dziedziczona po obserwatorze CTimerObserver
	virtual void refresh();
};

#endif