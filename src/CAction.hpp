/**\file
* @author Czarek Zawadka
* @date 2010.02.28
* @version 0.6
* @class CAction CAction.hpp 
* @brief Klasa bazowa dla wszystkich akcji wykonywanych przez gracza
*
* @todo zamienic asercje na sprytne testy z boosta
* @ todo przemyslec co powinno byc public
*/
#ifndef CACTION_HPP
#define CACTION_HPP

#include <string>
//#include "CLogic.hpp"
//#include "CConstants.hpp"
#include <cassert>

class CLogic;

using namespace std;

class CAction
{
	friend class CLogic;

public:

	CAction();
	
	CAction(string s);

	bool active_;

	virtual void getScoreFromMiniGame(int pointsProfit) = 0;

protected:

	virtual bool initAction() = 0;
	virtual bool performAction() = 0;

	
	//virtual bool finishAction() = 0;

	//virtual CAction * create() = 0;
	
	//zrobic  z tego const??
	string name_;

	int manaCost_;
	
	int manaProfit_;

	int pointsProfit_;

	//czyja to jest akcja, 1 -teacher, 0-studenci
	bool whose_;

};
#endif