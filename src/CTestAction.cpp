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
	CAudioSystem::getInstance()->play_sound("dzwonek");
	return true;
}

CTestAction::CTestAction():CAction("CTestAction")
{

}

CAction * CTestAction::createCTestAction()
{
	return new CTestAction;
};