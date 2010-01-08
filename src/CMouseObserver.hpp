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


using namespace std;


class CMouseObserver
{
	friend class CInput;

protected:

		virtual void refresh() = 0;
		virtual ~CMouseObserver();
};

#endif
