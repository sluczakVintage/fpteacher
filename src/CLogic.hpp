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
#include <vector>
#include "CAudioSystem.hpp"
#include "CEngine.hpp"

class CAction;

using namespace std;

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

	bool prefIsTeacher_;

private:

	CLogic::CLogic();
	
	bool isTeacher_;

	unsigned int myPoints_;
	
	unsigned int myMana_;

	///punkty przeciwnika
	unsigned int opPoints_;

	bool initiated_;

	//dostêpne akcje
	std::vector<boost::shared_ptr<CAction> > avActions;
};
#endif
