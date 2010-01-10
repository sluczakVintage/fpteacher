/**
* @author Rafal Malinowski
* @date 2009.01.08
* @version 0.1_draft
* @class CGui CGui.hpp
* @brief klasa CGui bedzie odpowiedzialna za wyswietlanie i zarzadzanie gui
*	
*		
*/

#ifndef CGUI_H
#define CGUI_H

#include "CMouseObserver.hpp"
#include "SDL.h"
#include "SDL_mixer.h"
#include "CSingleton.hpp"
#include "CStaticEntity.hpp"
#include "CInput.hpp"
#include "CMouseEvent.hpp"
#include "CAudioSystem.hpp"

class CMouseObserver;
class CInput;
using namespace std;

class CGui : public CSingleton<CGui> , public CMouseObserver
{
	friend class CSingleton<CGui>;
	friend CInput;
public:

	///Konstruktor Domyslny
	CGui();
	///Destruktor
	~CGui();

	///Metoda inicjujaca encje zwiazane z gui
	void initGui();

private:
	
	/// odziedziczona wirtualna funkcja wykorzystywana przez CMouseObserver
	///@param CMO wskaznik na obiekt klasy CMouseEvent przechowujacej informacje o zdarzeniach zwiazanych z mysza
	virtual void refresh(CMouseEvent * CMO);
};
#endif

//~~CGui.hpp