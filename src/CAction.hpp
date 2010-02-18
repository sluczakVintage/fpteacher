/**\file
* @author Czarek Zawadka
* @date 2010.01.10
* @version 0.6
* @class CAction CAction.hpp 
* @brief Klasa bazowa dla wszystkich akcji wykonywanych przez gracza
*

*/
#ifndef CACTION_HPP
#define CACTION_HPP

#include <string>
#include "CLogic.hpp"

using namespace std;

class CAction
{
	friend class CLogic;

	virtual bool performAction() = 0;
	
	string name_;

	unsigned int cost_;
	
	unsigned int profit_;

	//czyja to jest akcja, 1 -teacher, 0-studenci
	bool whose_;

};
#endif