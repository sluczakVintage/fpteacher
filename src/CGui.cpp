/** @file CGui.cpp
* @author Rafal Malinowski
* @date 2009.01.08
* @version 0.1_draft
* @brief klasa CGui bedzie odpowiedzialna za wyswietlanie i zarzadzanie gui
*	
*		
*/

#include "CGui.hpp"

///Konstruktor Domyslny
CGui::CGui()
{
	cout << "CGui::CGui(): konstruktor domyslny" << endl;
}

///Destruktor
CGui::~CGui()
{
	cout << "CGui::CGui(): niszczenie" << endl;
}


///Metoda inicjujaca encje zwiazane z gui
void CGui::initGui()
{
	CInput::getInstance()->addMouseObserver(*this); // dodanie klasy gui obserwatorow klasy CInput

	new CStaticEntity(350.0, 20.0, 1.0, "..\\res\\graphics\\sprites\\gui\\play.png");
	new CStaticEntity(475.0, 20.0, 1.0, "..\\res\\graphics\\sprites\\gui\\pause.png");
	new CStaticEntity(600.0, 20.0, 1.0, "..\\res\\graphics\\sprites\\gui\\stop.png");
}

/// odziedziczona wirtualna funkcja wykorzystywana przez CMouseObserver
///@param CMO wskaznik na obiekt klasy CMouseEvent przechowujacej informacje o zdarzeniach zwiazanych z mysza
void CGui::refresh(CMouseEvent * CMO)
{
	// metoda ta decyduje ktory przycisk zostal wcisniety i podejmuje odpowiednie akcje
	if(	CMO->pressedX_<425 && CMO->pressedX_>350 && CMO->pressedY_<95 && CMO->pressedY_>20 && CMO->releasedX_<425 && CMO->releasedX_>350 && CMO->releasedY_<95 && CMO->releasedY_>20)
	{
		CAudioSystem::getInstance()->play_music("muzyka1");
	}
	else if (	CMO->pressedX_<550 && CMO->pressedX_>475 && CMO->pressedY_<95 && CMO->pressedY_>20 && CMO->releasedX_<550 && CMO->releasedX_>475 && CMO->releasedY_<95 && CMO->releasedY_>20)
	{
		CAudioSystem::getInstance()->pause_music("muzyka1");
	}
	else if (	CMO->pressedX_<675 && CMO->pressedX_>600 && CMO->pressedY_<95 && CMO->pressedY_>20 && CMO->releasedX_<675 && CMO->releasedX_>600 && CMO->releasedY_<95 && CMO->releasedY_>20)
	{
		CAudioSystem::getInstance()->stop_music("muzyka1");
	}
	else
	{
		//nie rob nic
	}
}

//~~CGui.cpp