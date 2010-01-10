/**
* @author Czarek Zawadka
* @date 2009.12.12
* @version 0.1_draft
* @brief klasa CTimer pozwala  klasom implementuj¹cym interfejs CTimerObserver na dostêp do timera z SDL'a. CTimer to singleton
*	
* @note korzystanie 
*	Korzystanie z CTimer polega na wywolaniu klasy addObserver i cieszeniu sie z dok³adnego odmierzania czasu, 
*	gdy ju¿ siê nacieszymy mo¿na wywo³aæ removeObserver. 
*
* @note dzialanie 
*	Dzia³anie klasy CTimer polega na obudowaniu SDL'a. Wykorzystywana jest metoda SDL_AddTimer(Uint32 interval, SDL_NewTimerCallback callback, void* param),
*	ktora za³atwia wszystko. Parametry tej funkcji to: interval - odmierzany czas, callback - funkcja ktora ma 
*	zostaæ wywo³ana po odliczeniu do koñca, param - argument z ktorym ma byæ wywolana funkcja callback. 
*	W CTimer zosta³a zdefiniowana funkcja timerCallback, ktora jest uzywana jako callback. Parametremi s¹: interval(wymagane przez SDL) 
*	oraz  wskaŸnik na *	zainteresowanego CTimerObserver'a.
*
* @todo wzbogacenie klasy o mozliwosc pauzowania timera
* @todo dodac inicjalizacje SLD_Timera gdy to jeszcze nie nastapilo
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
	friend class CSingleton<CTimer>;

public:

	///rejestrowanie obserwatora. Poczatek odmierzania czasu jest natychmiasowy
	///@param CTimerObserver& o - obserwator ktory bedzie powiadamiany
	///@param int interval - odmierzany czas
	///@return SDL_TimerID - id kotre przypisano
	SDL_TimerID addObserver(CTimerObserver& o, int interval);	
	///usuwanie obserwatora
	void removeObserver(const CTimerObserver& o);
	
	//void start(const CTimerObserver& o);
	//void stop(const CTimerObserver& o);

	///pozwala uzyskaæ aktualny czas(liczony od uruchomienia SDL), lub czas jaki min¹³ od refTime
	///@param refTime - czas od ktorego ma byæ liczony aktualny czas
	int getTime(int refTime = 0);

	///Klasa opakowujaca SDL_Delay, sterowanie wraca do miejsca wywolania o delayTime milisekundach
	///@param int delayTime w milisekundach, powinna byc wielokrotnosc 40ms
	void delay(int delayTime);

private:
	///wskaŸnik na ta metode jest argumentem funkcji SDL_AddTimer(), tutaj realizowane jest 
	///powiadamianie obserwatorow 
	///@param interval - odmierzany czas
	///@param param - wskaznik na obserwatora dla ktorego odmierzany jest czas
	static Uint32 timerCallback(Uint32 interval, void* param);

	///Konstruktor domyslny
	CTimer();

	///Destruktor
	~CTimer();

	///klucz do mapy observers_, dodanie obserwatora inkrementuje id_ o jeden dla kolejnych obserwatorow
	static int id_;

	///struktura opakowujaca CTimerObserver. Zawiera SDL_TimerID 
	struct TimerParam
	{
		SDL_TimerID timreId_;
		CTimerObserver * observer_;
	};

	///kontener przechowuj¹cy obserwatorow
	map<int, TimerParam> observers_;
};

#endif

