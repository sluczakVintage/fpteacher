#include "CAction.hpp"

//const string CAction::name_ = "CAction";

CAction::CAction():name_("CAction")
{
/*	CConstants * cc = CConstants::getInstance();
	//manaCost_ = cc->actionsDesc_.f
	AcDesMap::iterator it = 
		cc->actionsDesc_.find(string(typeid(*this).name()));
	cout<<string(typeid(*this).name());
	assert(it != cc->actionsDesc_.end());
	manaCost_ = (it->second.find("manaCost_"))->second;
	manaProfit_ = (it->second.find("manaProfit_"))->second;
	pointsProfit_ = (it->second.find("pointsProfit_"))->second;
	*/
}

CAction::CAction(string s):name_(s)
{

}