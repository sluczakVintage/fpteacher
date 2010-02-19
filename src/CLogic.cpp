/**\file CLogic.cpp
* @author Czarek Zawadka
* @date 2010.01.10
* @version 0.6
* @class CLogic CLogic.hpp 
* @brief ta klasa obsluguje (czêœæ) logiki gry
*
*/

#include "CLogic.hpp"

CLogic::CLogic()
{
	initiated_ = false;
}
bool CLogic::getIsTeacher()
{
	return isTeacher_;
}

void CLogic::init(bool whoAmI)
{
	//?@todo w tej funkcji powinna byc inicjalizowana mapa wszystkich mo¿liwych akcji
	if(!initiated_)
	{
		isTeacher_ = whoAmI;
		initiated_ = true;
		CTimer::getInstance()->addObserver(*this,60*1000); //tu jest zaszyty czas gry!!!
	}
	
}

void CLogic::refresh(int interval, SDL_TimerID timerIds)
{
	quit();
}
/*
void CLogic::refresh()
{
	;
}
*/

void CLogic::quit()
{
		CAudioSystem::getInstance()->play_sound("dzwonek");
		CTimer::getInstance()->delay(2000);
}

unsigned int CLogic::getMyPoints()
{
	return myPoints_;
}

unsigned int CLogic::getMyMana()
{
	return myMana_;
}

unsigned int CLogic::getOpPoints()
{
	return opPoints_;
}

void CLogic::performAction(string s)
{
//	CAction * = avActions
	std::map<string, ActionPtr>::iterator it = avActions.find(s);
	if(it != avActions.end())
	{
		ActionPtr ap = (*(avActions.find(s))).second;
		if(myMana_ >= ap->manaCost_)
		{
			if(ap->performAction())
			{	//jezeli akcja sie udala
				myMana_ += ap->manaProfit_;
				myPoints_ += ap->pointsProfit_;
			}
		}
	}
	else
	{
		///@todo CLogic::performAction(string s) - tu powinien byc wyjatek!!
		///@todo wyjatkiem(albo testem) powinno byc to, ze ktos probowal wywolac nie swoja akcje
		cout<<"CLogic::performAction(string s) nie ma takiej akcji"<<endl;
	}
}