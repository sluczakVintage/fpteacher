/**
* @author Czarek Zawadka
* @date 2009.12.12
* @version 0.1_draft
* @brief klasa CTimer pozwala  klasom implementuj¹cym interfejs CTimerObserver na dostêp do timera z SDL'a. CTimer to singleton
*	korzystanie z CTimer polega na wywolaniu klasy addObserver i cieszeniu sie z dok³adnego odmierzania czasu, 
*	gdy ju¿ siê nacieszymy mo¿na wywo³aæ removeObserver
*	
*/

#ifndef CTIMER_H
#define CTIMER_H

#include <map>
#include "CSingleton.hpp"
#include "CTimerObserver.hpp"
#include  "SDL.h"
using namespace std;

class CTimerObserver;

class CTimer : public CSingleton<CTimer>
{
	friend CSingleton<CTimer>;

public:
	///rejestrowanie obserwatora i od razu go startuje
	void addObserver(CTimerObserver& o, int interval);					
	void removeObserver(const CTimerObserver& o);
	
	//void start(const CTimerObserver& o);
	//void stop(const CTimerObserver& o);
	static Uint32 timerCallback(Uint32 interval, void* param);

private:
	CTimer();
	~CTimer();
	map<int, CTimerObserver *> observers_;
	static int id_;
};

#endif

