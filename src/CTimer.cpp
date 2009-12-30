#include "CTimer.hpp"

///inicjalizacja statycznego id
int CTimer::id_=0;

CTimer::CTimer()
{
}

CTimer::~CTimer()
{
}

///metoda wywolywana przez  SDL 
///@return zwracany jest czas interval co powoduje kolejne odliczanie
Uint32 CTimer::timerCallback(Uint32 interval, void* param)
{
	TimerParam * tp = reinterpret_cast<TimerParam *>(param);
	tp->observer_->refresh();
	tp->observer_->refresh(interval, tp->timreId_);
	return interval; 
}

///w tej metodzie wywolywane jest SDL_AddTimer(interval, &timerCallback, &o), rozpoczyna sie odmierzanie 
///po dodatniu kolejnego CTimerObserver zwiekszany jest id_;
///@param CTimerObserver& o - obserwator ktory bedzie powiadamiany
///@param int interval - odmierzany czas
///@return SDL_TimerID - id kotre przypisano
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

///usuwanie CTimerObserwera - nie bedzie juz dostawac powiadomien
///@param CTimerObserver& o - obserwator do usuniecia
void CTimer::removeObserver(const CTimerObserver& o)
{
	set<SDL_TimerID>::iterator it;
	for(it = o.timerIds_.begin(); it != o.timerIds_.end(); it++ )
		SDL_RemoveTimer(*it);
}

/*
void start(const CTimerObserver& o);
void stop(const CTimerObserver& o);
*/
int CTimer::getTime(int refTime)
{

	return SDL_GetTicks() - refTime;
}
