/**\file
* @author Rafal Malinowski
* @date 2009.01.07
* @version 0.6
* @class CKeyObserver CKeyObserver.hpp
* @brief klasa CKeyObserver jest abstrakcyjna klasa po ktorej beda dziedziczyc wszystkie klasy zainteresowane obsluga klawiatury
*	
*		
*/
#ifndef CKEY_OBSERVER
#define CKEY_OBSERVER

#include "SDL.h"
#include <iostream>
//#include "CSingleton.hpp"
//#include "COGLWindow.hpp"
#include "CInput.hpp"
#include "CLog.hpp"
#include "keys.hpp"

using namespace std;

class CKeyObserver
{
	friend class CInput;

public:

	CKeyObserver();

	int getId() const;

	int getCounter() const;
protected:

	int id_;

	static int obsCounter_; 

	virtual void KeyPressed(SDLKey key, bool pressed) = 0;
};

#endif

//~~CKeyObserver.hpp