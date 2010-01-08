/**
* @author Rafal Malinowski
* @date 2009.01.08
* @version 0.1_draft
* @brief klasa CGui bedzie odpowiedzialna za wyswietlanie i zarzadzanie gui
*	
*		
*/

#ifndef CGUI_H
#define CGUI_H

#include "CMouseObserver.hpp"
//#include <iostream>
//#include <string>
#include "SDL.h"
#include "SDL_mixer.h"
#include "CSingleton.hpp"
//#include "CEntity.hpp"
#include "CStaticEntity.hpp"
#include "CInput.hpp"
#include "CMouseEvent.hpp"
#include "CAudioSystem.hpp"



class CMouseObserver;
class CInput;
using namespace std;

class CGui : public CSingleton<CGui> , public CMouseObserver
{
	friend CSingleton<CGui>;
	friend CInput;
	//friend CMouseObserver;
public:

	///Konstruktor Domyslny
	CGui();
	///Destruktor Domyslny
	~CGui();

	///inicjuje wszystko co zwiazane z gui
	void initGui();



private:

	virtual void refresh(CMouseEvent * CMO);
};
#endif