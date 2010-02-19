/**\file
* @author Czarek Zawadka
* @date 2010.01.10
* @version 0.6
* @class CLogic CLogic.hpp 
* @brief ta klasa obsluguje (czêœæ) logiki gry
*
* @todo isTeacher prywatne
*
*/
#ifndef CLOGIC_HPP
#define CLOGIC_HPP

#include  "CSingleton.hpp"
#include  "CAction.hpp"
#include <boost/shared_ptr.hpp>
#include "CTimerObserver.hpp"
#include <map>
#include "CAudioSystem.hpp"
#include "CEngine.hpp"
#include <string>

class CAction;

using namespace std;

typedef boost::shared_ptr<CAction> ActionPtr;

class CLogic : public CSingleton<CLogic>, public CTimerObserver 
{
	friend class CSingleton<CLogic>;

public:

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

private:

	CLogic::CLogic();
	
	bool isTeacher_;

	unsigned int myPoints_;
	
	unsigned int myMana_;

	///punkty przeciwnika
	unsigned int opPoints_;

	bool initiated_;

	//dostêpne akcje
	//std::map<boost::shared_ptr<CAction> > avActions;
	//nie jestem pewien, czy ta mapa powinna tak wygladac
	//kluczem jest nazwa zdarzenia
	std::map<string, ActionPtr> avActions;
};
#endif
