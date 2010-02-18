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
	if(!initiated_)
	{
		isTeacher_ = whoAmI;
		initiated_ = true;
		CTimer::getInstance()->addObserver(*this,60*1000);
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
		CEngine::getInstance()->setMouseQuitFlag(true);
}