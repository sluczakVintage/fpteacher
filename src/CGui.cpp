/** @file CGui.cpp
* @author Rafal Malinowski
* @date 2009.01.08
* @version 0.6
* @brief klasa CGui bedzie odpowiedzialna za wyswietlanie i zarzadzanie gui
*	
*		
*/

#include "CGui.hpp"
using namespace logging;

///Konstruktor Domyslny
CGui::CGui(): CKeyObserver()
{
	CLog::getInstance()->sss << "CGui::CGui(): konstruktor domyslny" << endl;
	logs(CLog::getInstance()->sss.str(), INFO);	
}

///Destruktor
CGui::~CGui()
{
	CLog::getInstance()->sss << "CGui::CGui(): niszczenie" << endl;
	logs(CLog::getInstance()->sss.str(), INFO);	
}


///Metoda inicjujaca encje zwiazane z gui
void CGui::initGui()
{
	setId();
	CInput::getInstance()->addMouseObserver(*this, 0, 10, 0, 10); // dodanie klasy gui obserwatorow klasy CInput
	CInput::getInstance()->addKeyObserver(*this);
	//CInput::getInstance()->addMouseObserver(*this); // dodanie klasy gui obserwatorow klasy CInput
	moveObserver_=true;
	new CStaticEntity(360.0, 0.0, 60.0, "../res/graphics/gui/background.png");
	new CStaticEntity(441.0, 10.0, 61.0, "../res/graphics/gui/play.png");  //ROZMIAR 30x30
	new CStaticEntity(495.0, 10.0, 61.0, "../res/graphics/gui/pause.png"); //ROZMIAR 30x30
	new CStaticEntity(552.0, 10.0, 61.0, "../res/graphics/gui/stop.png"); //ROZMIAR 30x30
	new CStaticEntity(907.0, 5.0, 61.0, "../res/graphics/gui/exit.png"); //ROZMIAR 30x30

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
//		CAudioSystem::getInstance()->play_sound("dzwonek");
//		CTimer::getInstance()->delay(2000);
//		CEngine::getInstance()->setMouseQuitFlag(true);
		//// @todo przeniesiono do logiki -> ju¿ nie
		///  JU¯ NIE..., czêœciowo wróci³o z powrotem
		/// Trzeba rozwi¹zaæ konflikty z include'ami...
		CLogic::getInstance()->quit();
		CEngine::getInstance()->setMouseQuitFlag(true);
	}
	else
	{
		//nie rob nic
	}
}

void CGui::mouseIsOver(bool over)
{
	if (over) 
	{
		CLog::getInstance()->sss << "CGui::mouseIsOver: wjechano myszka nad obiekt;" << endl;
		logs(CLog::getInstance()->sss.str(), INFO);
	}
	else  
	{
		CLog::getInstance()->sss << "CGui::mouseIsOver: zjechano myszka z obiektu;" << endl;
		logs(CLog::getInstance()->sss.str(), INFO);
	}
	setMoveIsOver(over);
}

void CGui::KeyPressed(SDLKey key, bool pressed)
{
	if(pressed)
	{
		CLog::getInstance()->sss << "CGui::KeyPressed: wcisnieto klawisz nr;" << key << endl;
		logs(CLog::getInstance()->sss.str(), TEMP);
	}
	else
	{
		CLog::getInstance()->sss << "CGui::KeyPressed: odcisnieto klawisz;" << key << endl;
		logs(CLog::getInstance()->sss.str(), TEMP);
	}
}
//~~CGui.cpp
