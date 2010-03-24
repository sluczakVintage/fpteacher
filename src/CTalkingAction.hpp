/**\file
* @author Rafal Malinowski
* @date 2010.03.01
* @version 0.6
* @class CTalkingAction CTalkingAction.hpp 
* @brief Klasa akcji odpowiedzialnej za gadanie
*

*/
#ifndef CTALKINGACTION_H
#define CTALKINGACTION_H

#include <string>
#include "CAction.hpp"
#include "CAudioSystem.hpp"
//#include "CAuditorium.hpp"

//class CAuditorium;
class CAction;
using namespace std;

class CTalkingAction : public CAction
{

public:

	CTalkingAction();
	
	//static CAction * createCTestAction();

protected:

	virtual bool performAction();
	virtual bool initAction();
	virtual void getScoreFromMiniGame(int pointsProfit);
};

#endif