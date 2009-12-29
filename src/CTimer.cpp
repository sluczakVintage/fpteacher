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
	int i = id_++;
	o.id_ = i;
	TimerParam tp;
	observers_.insert(pair<int, TimerParam> (o.id_,tp));
	SDL_TimerID newTimerId = SDL_AddTimer(interval, &timerCallback, &(observers_[i]));
	o.timerIds_.insert(newTimerId);
	//tp = {newTimerId, &o};
	observers_[i].observer_ = &o;
	observers_[i].timreId_ = newTimerId;

	cout<<"CTimer::addObserver: dodano obserwatora CTimerObserver, odmierzany czas: "<<interval<<endl;
	return newTimerId;
}

///usuwanie CTimerObserwera - nie bedzie juz dostawac powiadomien
///@param CTimerObserver& o - obserwator do usuniecia
void CTimer::removeObserver(const CTimerObserver& o)
{
	//dodaæ try/catch
	cout<<"CTimer::removeObserver: usuwanie obserwatora CTimerObserver, o numerze id_:"<<o.id_<<endl;
	  set<SDL_TimerID>::iterator it;

	for(it = o.timerIds_.begin(); it != o.timerIds_.end(); it++ )
		SDL_RemoveTimer(*it);
}

	/*	void start(const CTimerObserver& o);
	void stop(const CTimerObserver& o);
*/
int CTimer::getTime(int refTime)
{

	return SDL_GetTicks() - refTime;
}
