/** @file CMouseEvent.cpp
* @author Rafal Malinowski
* @date 2009.01.08
* @version 0.6
* @brief klasa CMouseEvent odpowiada za przesylanie informacji na temat akcji myszy z klasy CInput do innych
*	
*		
*/
#include "CMouseEvent.hpp"
using namespace logging;

/// konstruktor domyslny
CMouseEvent::CMouseEvent()
{
	pressedX_=0;	// w konstruktorze domyslnym nastepuje zerowanie wszystkich pol
	pressedY_=0;
	releasedX_=0;
	releasedY_=0;
	currentX_=0;
	currentY_=0;
	pressed_=false;
	//cout << "CMouseEvent::CMouseEvent(): konstruktor domyslny" << endl;
}

/// destruktor
CMouseEvent::~CMouseEvent()
{
	//cout << "CMouseEvent::CMouseEvent(): niszczenie" << endl;
}

//~~CMouseEvent.cpp
