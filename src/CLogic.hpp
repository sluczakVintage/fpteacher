/**\file
* @author Czarek Zawadka
* @date 2010.01.10
* @version 0.6
* @class CLogic CLogic.hpp 
* @brief ta klasa obsluguje (czêœæ) logiki gry
*
*
*/
#ifndef CLOGIC_HPP
#define CLOGIC_HPP

#include <boost/smart_ptr.hpp>
#include "CTimerObserver.hpp"
#include <map>
#include "CAudioSystem.hpp"

//#include "CEngine.hpp"
#include <string>
#include <boost/function.hpp>
#include "CSingleton.hpp"
#include "CAction.hpp"
#include "CConstants.hpp"
#include "CTestAction.hpp"
#include "CLog.hpp"
#include "CTalkingAction.hpp"
#include "CKeyObserver.hpp"

class CAction;
class CTestAction;
class CAuditorium;

using namespace std;
using namespace logging;
//typedef boost::shared_ptr<CAction> ActionPtr;
//typedef boost::bind ActionPtr;

class CLogic : public CSingleton<CLogic>, public CTimerObserver, CKeyObserver
{
	friend class CSingleton<CLogic>;

public:


	void initActions();

	bool getIsTeacher();

	///inicjalizacja klasy
	///@param whoAmI oznacza Nauczyciela(1) lub studenta (0)
	void init(bool whoAmI);

	virtual void refresh(int interval, SDL_TimerID timerIds);
	//virtual void refresh();
	
	//konczy gre - dzwonek. Wysyla info przez siec(gdy niszczone jest CNetwork).
	void quit();

	//flaga oznaczajaca czy ktos chce byc nauczycielem, czy studentami
	//ostatecznie w przypadku konfliktu decyduje klient w sieciowce
	bool prefIsTeacher_;

	unsigned int getMyPoints();

	unsigned int getMyMana();

	unsigned int getOpPoints();

	void performAction(string s);

	void performActions();

private:

	CLogic();
	
	bool isTeacher_;

	unsigned int myPoints_;
	
	unsigned int myMana_;

	///punkty przeciwnika
	unsigned int opPoints_;

	bool initiated_;

	SDL_TimerID quitTimer;
	
	SDL_TimerID manaTimer;

	//dostêpne akcje
	//std::map<boost::shared_ptr<CAction> > avActions;
	//nie jestem pewien, czy ta mapa powinna tak wygladac
	//kluczem jest nazwa zdarzenia
	//std::map<string, boost::bind(&CAction::create)> avActions;
	std::map <string, boost::function <CAction* (void)> > avActions;
	 
	std::map <string, CAction* > actions;

//	boost::function <CAction * (void)> creator;
//	boost::function<void (int, int)> pf;

	void fillUpAction(CAction & ca);

	virtual void KeyPressed(SDLKey key, bool pressed);

};
#endif
