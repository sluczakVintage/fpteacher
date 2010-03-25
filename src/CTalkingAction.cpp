/** @file CTalkingAction.cpp
* @author Rafal Malinowski
* @date 2010.03.24
* @version 0.1
* @brief 
*  
*		
*/

#include "CTalkingAction.hpp"
//using namespace std;

CTalkingAction::CTalkingAction(): CAction()
{
	name_="CTalkingAction";
	slider = new CSlider();
}

bool CTalkingAction::initAction()
{
	//slider = new CSlider();
	slider->initGame(this);
	return true;
}

bool CTalkingAction::performAction()
{
	cout << "dzialam sobie ;)" << endl;
	slider->drawIt();
	return true;
}


void CTalkingAction::getScoreFromMiniGame(int pointsProfit)
{
	pointsProfit_=pointsProfit;
	cout << "liczba punktow to: " << pointsProfit << endl;
	active_=false;
	//delete slider;
	CLogic::getInstance()->changePoints(pointsProfit, manaProfit_, 0);
}