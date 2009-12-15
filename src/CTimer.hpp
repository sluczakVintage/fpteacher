/**
* @author Czarek Zawadka
* @date 2009.12.12
* @version 0.1_draft
* @brief klasa CTimer pozwala  klasom implementuj¹cym interfejs CTimerObserver na dostêp do timera z SDL'a. CTimer to singleton
*	
* @page korzystanie 
*	Korzystanie z CTimer polega na wywolaniu klasy addObserver i cieszeniu sie z dok³adnego odmierzania czasu, 
*	gdy ju¿ siê nacieszymy mo¿na wywo³aæ removeObserver. 
*
* @page dzialanie 
*	Dzia³anie klasy CTimer polega na obudowaniu SDL'a. Wykorzystywana jest metoda SDL_AddTimer(Uint32 interval, SDL_NewTimerCallback callback, void* param),
*	która za³atwia wszystko. Parametry tej funkcji to: interval - odmierzany czas, callback - funkcja która ma 
*	zostaæ wywo³ana po odliczeniu do koñca, param - argument z którym ma byæ wywolana funkcja callback. 
*	W CTimer zosta³a zdefiniowana funkcja timerCallback, ktora jest uzywana jako callback. Parametremi s¹: interval(wymagane przez SDL) 
*	oraz  wskaŸnik na *	zainteresowanego CTimerObserver'a.
*
* @todo dodanie parametru metody addObserver oznaczaj¹ce funkcjê wywo³ywan¹ gdy zostanie odmierzony zadany czas
* @todo wzbogacenie klasy o mozliwosc pauzowania timera
* @todo wzbogaci klasy CTimer oraz CTimerObserver tak, aby jedna instancja CTimerObserver mogla obserwowac
*	kilka roznych zegarow
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

	///rejestrowanie obserwatora. Pocz¹tek odmierzania czasu jest natychmiasowy
	void addObserver(CTimerObserver& o, int interval);	
	///usuwanie obserwatora
	void removeObserver(const CTimerObserver& o);
	
	//void start(const CTimerObserver& o);
	//void stop(const CTimerObserver& o);

	///wskaŸnik na t¹ metodê jest argumentem funkcji SDL_AddTimer(), tutaj realizowane jest 
	///powiadamianie obserwatorów @ref dzialanie
	
	///@param interval - odmierzany czas
	///@param param - wskaŸnik na obserwatora dla którego odmierzany jest czas
	static Uint32 timerCallback(Uint32 interval, void* param);

private:

	///Konstruktor domyslny
	CTimer();
	///Destruktor
	~CTimer();
	///kontener przechowuj¹cy obserwatorów
	map<int, CTimerObserver *> observers_;
	///klucz do mapy observers_, dodanie obserwatora inkrementuje id_ o jeden dla kolenych obserwatorow
	static int id_;
};

#endif

