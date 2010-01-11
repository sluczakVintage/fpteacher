/** @file CTimerObserver.cpp
* @author Czarek Zawadka
* @date 2009.12.12
* @version 0.1_draft
* @brief klasa CTimerObserver to interfejs dla klas korzystajacych z CTimer
*
* @todo przeciazyc w klasach pochodnych virtual void refresh(int interval, SDL_TimerID timerIds) tak, aby ta metoda mogla byc abstrakcyjna
* @todo metoda virtual void refresh() zostanie usunieta
* 
*/

#include "CTimerObserver.hpp"

///destruktor powoduje wyrejestrowanie sie z obserwatorow CTimer'a. jezli juz to zostalo zrobione 
///to nic zlego nie powinno sie zdarzyc
CTimerObserver::~CTimerObserver()
{
	std::cout<<"CTimerObserver::~CTimerObserver: niszczenie"<<std::endl; 
	CTimer::getInstance()->removeObserver(*this);
		
}
