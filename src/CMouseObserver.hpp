/**\file
* @author Rafal Malinowski
* @date 2009.01.07
* @version 0.6
* @class CMouseObserver CMouseObserver.hpp
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

public:

	void setMoveObserver (bool x);

	bool getMoveObserver();
protected:

	/// wirtualna metoda wywolywana przez klase CInput we wszystkich dziedziczacych klasach (wywolywana podczas klikniec)
	virtual void refresh(CMouseEvent * CMO) = 0;

	/// wirtualna metoda wywolywana przez klase CInput we wszystkich dziedziczacych klasach (wywolywana podczas ruchu)
	virtual void refreshMove(CMouseEvent * CMO) = 0;

	/// destruktor wirutalny
	virtual ~CMouseObserver();

	/// flaga mowiaca czy observatora interesuje tylko klikanie myszy czy takze ruch
	bool moveObserver_;

};

#endif

//~~CMouseObserver.hpp