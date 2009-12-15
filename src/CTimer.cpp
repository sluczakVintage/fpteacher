#include "CTimer.hpp"

///inicjalizacja statycznego id
int CTimer::id_=0;

CTimer::CTimer()
{
}

CTimer::~CTimer()
{
}

///metoda wywolywana przez  SDL @ref dzialanie
///@return zwracany jest czas interval co powoduje kolejne odliczanie
Uint32 CTimer::timerCallback(Uint32 interval, void* param)
{
	CTimerObserver * cto = reinterpret_cast<CTimerObserver *>(param);
	cto->refresh();
	return interval; 
}
///w tej metodzie wywolywane jest SDL_AddTimer(interval, &timerCallback, &o), rozpoczyna sie odmierzanie @ref dzialanie
///po dodatniu kolejnego CTimerObserver zwiekszany jest id_;
///@param CTimerObserver& o - obserwator ktory bedzie powiadamiany
///@param int interval - odmierzany czas
void CTimer::addObserver(CTimerObserver& o, int interval)
{
	o.id_ = id_++;
	observers_.insert(pair<int, CTimerObserver *> (o.id_, &o));
	o.timerId_ = SDL_AddTimer(interval, &timerCallback, &o);
	cout<<"CTimer::addObserver: dodano obserwatora CTimerObserver, odmierzany czas: "<<interval<<endl;
}

///usuwanie CTimerObserwera - nie bedzie juz dostawac powiadomien
///@param CTimerObserver& o - obserwator do usuniecia
void CTimer::removeObserver(const CTimerObserver& o)
{
	//dodaæ try/catch
	cout<<"CTimer::removeObserver: usuwanie obserwatora CTimerObserver, o numerze id_:"<<o.id_<<endl;
	SDL_RemoveTimer(o.timerId_);
}

	/*	void start(const CTimerObserver& o);
	void stop(const CTimerObserver& o);
*/
