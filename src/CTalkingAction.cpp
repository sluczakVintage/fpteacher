/** @file CTalkingAction.cpp
* @author Rafal Malinowski
* @date 2010.03.24
* @version 0.1
* @brief 
*  
*		
*/

#include "CTalkingAction.hpp"


CTalkingAction::CTalkingAction()
{
	
}

bool CTalkingAction::performAction()
{
	cout << "dzialam sobie ;)" << endl;
	return true;
}

bool CTalkingAction::initAction()
{
	return true;
}

void CTalkingAction::getScoreFromMiniGame(int pointsProfit)
{
}