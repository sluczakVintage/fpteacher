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

using namespace std;

class CEngine : public CSingleton<CEngine>
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
	
};

#endif