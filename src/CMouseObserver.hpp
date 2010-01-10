/**
* @author Rafal Malinowski
* @date 2009.01.07
* @version 0.1_draft
* @brief klasa CMouseObserver jest abstrakcyjna klasa po ktorej beda dziedziczyc wszystkie klasy zainteresowane obsluga myszy
*	
*		
*/
#ifndef CMOUSE_OBSERVER
#define CMOUSE_OBSERVER

#include <cassert>
#include "SDL.h"
#include <iostream>
#include "CSingleton.hpp"
#include "COGLWindow.hpp"
#include "CInput.hpp"
#include "CMouseEvent.hpp"

using namespace std;

class CMouseObserver
{
	friend class CInput;

protected:

	/// wirtualna metoda wywolywana przez klase CInput we wszystkich dziedziczacych klasach
	virtual void refresh(CMouseEvent * CMO) = 0;

	/// destruktor wirutalny
	virtual ~CMouseObserver();
};

#endif

//~~CMouseObserver.hpp