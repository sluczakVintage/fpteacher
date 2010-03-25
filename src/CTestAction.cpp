/**\file CAction.cpp 
* @author Czarek Zawadka
* @date 2010.03.01
* @version 0.6
* 
* @brief Klasa akcji testowej
*
*/
#include "CTestAction.hpp"

bool CTestAction::performAction()
{
	
//	CTimer::getInstance()->delay(10000);
	//int i = (CAuditorium::getInstance()->getFieldPtr(500,500))->getId().first;
	//int j = (CAuditorium::getInstance()->getFieldPtr(500,500))->getId().second;
	return true;
}

bool CTestAction::initAction()
{
	CAudioSystem::getInstance()->play_sound("dzwonek");
	CLogic::getInstance()->changePoints(pointsProfit_, manaProfit_, 0);
	return true;
}

CTestAction::CTestAction():CAction("CTestAction")
{

}

CAction * CTestAction::createCTestAction()
{
	return new CTestAction;
};

void CTestAction::getScoreFromMiniGame(int pointsProfit)
{

}