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

	new CStaticEntity(360.0, 0.0, 60.0, "..\\res\\graphics\\gui\\background.png");
	new CStaticEntity(441.0, 10.0, 61.0, "..\\res\\graphics\\gui\\play.png");  //ROZMIAR 30x30
	new CStaticEntity(495.0, 10.0, 61.0, "..\\res\\graphics\\gui\\pause.png"); //ROZMIAR 30x30
	new CStaticEntity(552.0, 10.0, 61.0, "..\\res\\graphics\\gui\\stop.png"); //ROZMIAR 30x30
	new CStaticEntity(907.0, 5.0, 61.0, "..\\res\\graphics\\gui\\exit.png"); //ROZMIAR 30x30

	/*new CStaticEntity(350.0, 20.0, 1.0, "..\\res\\graphics\\sprites\\gui\\play.png");
	new CStaticEntity(475.0, 20.0, 1.0, "..\\res\\graphics\\sprites\\gui\\pause.png");
	new CStaticEntity(600.0, 20.0, 1.0, "..\\res\\graphics\\sprites\\gui\\stop.png");*/
}

/// odziedziczona wirtualna funkcja wykorzystywana przez CMouseObserver
///@param CMO wskaznik na obiekt klasy CMouseEvent przechowujacej informacje o zdarzeniach zwiazanych z mysza
void CGui::refresh(CMouseEvent * CMO)
{
	// metoda ta decyduje ktory przycisk zostal wcisniety i podejmuje odpowiednie akcje
	if(	CMO->pressedX_<471 && CMO->pressedX_>441 && CMO->pressedY_<40 && CMO->pressedY_>10 && CMO->releasedX_<471 && CMO->releasedX_>441 && CMO->releasedY_<40 && CMO->releasedY_>10)
	{
		CAudioSystem::getInstance()->play_music("muzyka1");
	}
	else if (	CMO->pressedX_<525 && CMO->pressedX_>495 && CMO->pressedY_<40 && CMO->pressedY_>10 && CMO->releasedX_<525 && CMO->releasedX_>495 && CMO->releasedY_<40 && CMO->releasedY_>10)
	{
		CAudioSystem::getInstance()->pause_music("muzyka1");
	}
	else if (	CMO->pressedX_<582 && CMO->pressedX_>552 && CMO->pressedY_<40 && CMO->pressedY_>10 && CMO->releasedX_<582 && CMO->releasedX_>552 && CMO->releasedY_<40 && CMO->releasedY_>10)
	{
		CAudioSystem::getInstance()->stop_music("muzyka1");
	}
	else if (	CMO->pressedX_<1019 && CMO->pressedX_>907 && CMO->pressedY_<57 && CMO->pressedY_>5 && CMO->releasedX_<1019 && CMO->releasedX_>907 && CMO->releasedY_<57 && CMO->releasedY_>5)
	{
		CEngine::getInstance()->setMouseQuitFlag(true);
	}
	else
	{
		//nie rob nic
	}
}

//~~CGui.cpp