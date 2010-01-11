/**
* @author Czarek Zawadka
* @date 2009.12.12
* @version 0.1_draft
* @class CTimerObserver CTimerObserver.hpp
* @brief klasa CTimerObserver to interfejs dla klas korzystajacych z CTimer
*
* @todo przeciazyc w klasach pochodnych virtual void refresh(int interval, SDL_TimerID timerIds) tak, aby ta metoda mogla byc abstrakcyjna
* @todo metoda virtual void refresh() zostanie usunieta
* 
*/

#ifndef CTIMER_OBSERVER_H
#define CTIMER_OBSERVER_H

#include <set>
#include "CTimer.hpp"
#include "SDL.h"
#include <iostream>

class CTimerObserver{
	///potrzebme aby CTimer mogl sie dobieraæ do prywatnych skladowych tej klasy
	friend class CTimer;				

//protected:
protected:
	/// jedyna metoda jak¹ powinna implementowaæ kalsa dziedziczaca po tym interfejsie	
	virtual void refresh(){};
	///CZAREK
	virtual void refresh(int interval, SDL_TimerID timerIds){};
	
	/// potrzebne, aby klasy pochodne mogly po sobie elegancko posprzatac
	virtual ~CTimerObserver();

private:
	/// id obserwowanego zegara
	mutable std::set <SDL_TimerID> timerIds_;

};
#endif
