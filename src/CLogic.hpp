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

class CAction;

using namespace std;

class CLogic : public CSingleton<CLogic>
{
	friend class CSingleton<CLogic>;

public:

	bool getIsTeacher();

	//to powinno byc prywatne
	bool isTeacher;

private:
	
	unsigned int myPoints;
	
	unsigned int myMana;

	unsigned int opPoints;
};
#endif
