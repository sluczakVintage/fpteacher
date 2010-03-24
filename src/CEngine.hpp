/** \file
* 
* @author Rafal Malinowski
* @date 2009.12.07
* @version 0.6
* @class CEngine CEngine.hpp
* @brief klasa CEngine odpowiada za poprawne dzialanie silnika gry
*
*		
*/
#ifndef CENGINE
#define CENGINE

#include <boost/smart_ptr.hpp>

#include <cassert>
#include "SDL.h"
#include "SDL_mixer.h"
#include <iostream>
#include <fstream>
#include <sstream>

#include "CSingleton.hpp"
#include "COGLWindow.hpp"
#include "CInput.hpp"
#include "CLogic.hpp"
#include "CWorld.hpp"
#include "CTimer.hpp"
#include "CTimerObserver.hpp"
#include "CSpriteMgr.hpp"
#include "CAnimationMgr.hpp"
#include "utils.hpp"
#include "CNetwork.hpp"
#include "CAuditorium.hpp"
#include "CGui.hpp"
#include "CFontMgr.hpp"
/// @ROBOCZE
#include "CLog.hpp"
#include "CThrow.hpp"
#include "CGuiMenu.hpp"
//#include "CSlider.hpp"
//#include "CBalance.hpp"



using namespace std;

class CEngine : public CSingleton<CEngine>, public CTimerObserver
{
	friend class CSingleton<CEngine>;
public:

	///metoda w ktorej odpalany jest sdl, oraz uruchamiane sa konstruktory wielu klas (COGLWindow, CInput itd...)
	bool init();
	///metoda posiadajaca glowna petle programu
	void start();
	///metoda odpowiedzialna za zamykanie SDLa oraz ewentualne aktywowanie destruktorow roznych klas
	void end();

	///metoda ktora ustawia flage mouse_quit_flag_
	void setMouseQuitFlag(bool quit);

private:
	///konstruktor domyslny
	CEngine();
	///destruktor domyslny
	~CEngine();	

	/// flaga, dzieki ktorej zostaje ukonczony program poprzez klikniecie obrazka exit myszka
	bool mouse_quit_flag_;
	/// flaga ktora przyjmuje wartosc true jesli ma byc robiony refresh przy pomocy obserwatora i wartosc false w przeciwnej sytuacji
	bool refresh_flag;
	/// flaga ktora oznacza iz nadszedl czas refresha
	bool refresh_enable;
	/// metoda dziedziczona po obserwatorze CTimerObserver
	virtual void refresh();
};


#endif

//~~CEngine.hpp