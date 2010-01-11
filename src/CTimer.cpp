/** @file CTimer.cpp
* @author Czarek Zawadka
* @date 2009.12.12
* @version 0.1_draft
* @brief klasa CTimer pozwala  klasom implementujacym interfejs CTimerObserver na dostep do timera z SDL'a. CTimer to singleton
*	
* @note korzystanie 
*	Korzystanie z CTimer polega na wywolaniu klasy addObserver i cieszeniu sie z dokladnego odmierzania czasu, 
*	gdy juz sie nacieszymy mozna wywolac removeObserver. 
*
* @note dzialanie 
*	Dzialanie klasy CTimer polega na obudowaniu SDL'a. Wykorzystywana jest metoda SDL_AddTimer(Uint32 interval, SDL_NewTimerCallback callback, void* param),
*	ktora zalatwia wszystko. Parametry tej funkcji to: interval - odmierzany czas, callback - funkcja ktora ma 
*	zostac wywolana po odliczeniu do koñca, param - argument z ktorym ma byc wywolana funkcja callback. 
*	W CTimer zostala zdefiniowana funkcja timerCallback, ktora jest uzywana jako callback. Parametremi sa: interval(wymagane przez SDL) 
*	oraz  wskaznik na *	zainteresowanego CTimerObserver'a.
*
* @todo wzbogacenie klasy o mozliwosc pauzowania timera
*/

#include "CTimer.hpp"

//inicjalizacja statycznego id
int CTimer::id_=0;

CTimer::CTimer()
{
}

CTimer::~CTimer()
{
	observers_.clear();
}

//metoda wywolywana przez  SDL 
Uint32 CTimer::timerCallback(Uint32 interval, void* param)
{
	TimerParam * tp = reinterpret_cast<TimerParam *>(param);
	tp->observer_->refresh();
	tp->observer_->refresh(interval, tp->timreId_);
	return interval; 
}

//w tej metodzie wywolywane jest SDL_AddTimer(interval, &timerCallback, &o), rozpoczyna sie odmierzanie 
//po dodatniu kolejnego CTimerObserver zwiekszany jest id_;
SDL_TimerID CTimer::addObserver(CTimerObserver& o, int interval)
{
	TimerParam tp;
	observers_.insert(pair<int, TimerParam> (id_,tp));
	SDL_TimerID newTimerId = SDL_AddTimer(interval, &timerCallback, &(observers_[id_]));
	o.timerIds_.insert(newTimerId);
	observers_[id_].observer_ = &o;
	observers_[id_].timreId_ = newTimerId;
	cout<<"CTimer::addObserver: dodano obserwatora CTimerObserver, odmierzany czas: "<<interval<<" newTimerId  "<<newTimerId<<" id "<<id_ <<endl;
	id_++;
	
	return newTimerId;
}

//usuwanie CTimerObserwera - nie bedzie juz dostawac powiadomien
void CTimer::removeObserver(const CTimerObserver& o)
{
	set<SDL_TimerID>::iterator it;
	for(it = o.timerIds_.begin(); it != o.timerIds_.end(); it++ )
	{
		SDL_RemoveTimer(*it);
	}
}

/*
void start(const CTimerObserver& o);
void stop(const CTimerObserver& o);
*/
int CTimer::getTime(int refTime)
{

	return SDL_GetTicks() - refTime;
}

//Klasa opakowujaca SDL_Delay, sterowanie wraca do miejsca wywolania o delayTime milisekundach
void CTimer::delay(int delayTime)
{
	SDL_Delay(delayTime);
}