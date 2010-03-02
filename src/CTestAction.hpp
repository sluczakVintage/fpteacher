/**\file
* @author Czarek Zawadka
* @date 2010.03.01
* @version 0.6
* @class CTestAction CTestAction.hpp 
* @brief Klasa akcji testowej
*

*/
#ifndef CTESTACTION_HPP
#define CTESTACTION_HPP

#include <string>
#include "CAction.hpp"
#include "CAudioSystem.hpp"

class CAction;
using namespace std;

class CTestAction : public CAction
{

public:

	CTestAction();
	
	static CAction * createCTestAction();

protected:

	virtual bool performAction();

};

#endif