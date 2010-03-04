/**\file CLogic.cpp
* @author Czarek Zawadka
* @date 2010.01.10
* @version 0.6
*  
* @brief ta klasa obsluguje (czêœæ) logiki gry
*
*/

#include "CLogic.hpp"

CLogic::CLogic()
{
	initiated_ = false;
}
bool CLogic::getIsTeacher()
{
	return isTeacher_;
}

void CLogic::init(bool whoAmI)
{
	if(!initiated_)
	{
		isTeacher_ = whoAmI;
		initiated_ = true;
		CConstants * cc = CConstants::getInstance();
		myPoints_ = 0;
		myMana_ = 100;
		opPoints_ = 0;
		
		//tutaj zapisuja sie funkcje tworzace obiekty akcji!!
		if(isTeacher_ ==1)
		{//akcje nauczyciela
			string s = "CTestAction";
			boost::function <CAction * (void)> creator = &(CTestAction::createCTestAction);
			avActions.insert(make_pair(s, creator));
		}
		else
		{//akcje studentow
			string s = "CTestAction";
			boost::function <CAction * (void)> creator = &(CTestAction::createCTestAction);
			avActions.insert(make_pair(s, creator));
		}
		//~~
		manaTimer = CTimer::getInstance()->addObserver(*this, (60*1000)/(cc->manaVelocity_));

		quitTimer = CTimer::getInstance()->addObserver(*this,1000*(cc->gameTime_));
		
	}
	
}

void CLogic::refresh(int interval, SDL_TimerID timerIds)
{
	if(timerIds == manaTimer)
	{
		myMana_++;
	}
	else if(timerIds == quitTimer)
	{
		quit();
	}
	else
	{
		;//jakis komunikat bledu? moze,log
	}
}
/*
void CLogic::refresh()
{
	;
}
*/

void CLogic::quit()
{
		CAudioSystem::getInstance()->play_sound("dzwonek");
		CTimer::getInstance()->delay(2000);
}

unsigned int CLogic::getMyPoints()
{
	return myPoints_;
}

unsigned int CLogic::getMyMana()
{
	return myMana_;
}

unsigned int CLogic::getOpPoints()
{
	return opPoints_;
}

void CLogic::performAction(string s)
{
	std::map <string, boost::function <CAction* (void)> >::iterator it = avActions.find(s);
	if(it != avActions.end())
	{
		CAction * ca = (*(avActions.find(s))).second();
		this->fillUpAction(*ca);
		if(myMana_ >= ca->manaCost_)
		{
			if(ca->performAction())
			{	//jezeli akcja sie udala
				myMana_ += ca->manaProfit_;
				myPoints_ += ca->pointsProfit_;
			}
		}
		delete ca;
	}
	else
	{
		///@todo CLogic::performAction(string s) - tu powinien byc wyjatek!!
		///@todo wyjatkiem(albo testem) powinno byc to, ze ktos probowal wywolac nie swoja akcje
		//cout<<"CLogic::performAction(string s) nie ma takiej akcji"<<endl;
//		CLog::ge
	}

}

void CLogic::fillUpAction(CAction & ca)
{
	CConstants * cc = CConstants::getInstance();
	//manaCost_ = cc->actionsDesc_.f
	AcDesMap::iterator it = cc->actionsDesc_.find(ca.name_);
	//cout<<string(typeid(*this).name());
	assert(it != cc->actionsDesc_.end());
	std::map<string,unsigned int> * acMap = &(it->second);

	ca.manaCost_ = (it->second.find("manaCost"))->second;
	ca.manaProfit_ = (it->second.find("manaProfit"))->second;
	ca.pointsProfit_ = (it->second.find("pointsProfit"))->second;
	ca.whose_ =static_cast<bool>((it->second.find("whose"))->second);
	
}