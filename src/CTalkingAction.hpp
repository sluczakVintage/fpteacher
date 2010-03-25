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
#include <iostream>
#include "CAction.hpp"
//#include "CAudioSystem.hpp"
#include "CSlider.hpp"
//#include "CAuditorium.hpp"
#include "CLogic.hpp"
//class CAuditorium;
class CAction;
class CSlider;
using namespace std;

class CTalkingAction : public CAction
{

public:

	CTalkingAction();
	
	//static CAction * createCTestAction();
	virtual void getScoreFromMiniGame(int pointsProfit);

protected:

	virtual bool performAction();
	virtual bool initAction();

private:
	CSlider * slider;
};

#endif