#include "CTimer.hpp"

int CTimer::id_=0;
CTimer::CTimer()
{
	
}

CTimer::~CTimer()
{
}

Uint32 CTimer::timerCallback(Uint32 interval, void* param)
{
	CTimerObserver * cto = reinterpret_cast<CTimerObserver *>(param);
	cto->refresh();
	return interval; 
}

void CTimer::addObserver(CTimerObserver& o, int interval)
{
	o.id_ = id_++;
	
	observers_.insert(pair<int, CTimerObserver *> (o.id_, &o));
	o.timerId_ = SDL_AddTimer(interval, &timerCallback, &o);
}

void CTimer::removeObserver(const CTimerObserver& o)
{
	//dodaæ try/catch
	SDL_RemoveTimer(o.timerId_);
}

	/*	void start(const CTimerObserver& o);
	void stop(const CTimerObserver& o);
*/