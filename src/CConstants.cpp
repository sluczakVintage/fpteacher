/**\file CConstants.cpp
* @author Czarek Zawadka
* @date 2010.02.28
* @version 0.6
*
* @brief klasa, singleton, przechowuje stale
* 
*/
#include "CConstants.hpp"

CConstants* CConstants::mInstance_ = 0;


CConstants::CConstants()
{ 
	//actionsDesc_.insert(std::make_pair<string,boost::tuple<unsigned int,unsigned int,unsigned int> >("test",boost::make_tuple(
	//actionsDesc_.insert(make_pair("test",boost::make_tuple(10, 15, 10)));
//	std::vector<unsigned int> v;
//	v.push_back(10);
//	v.push_back(15);
//	v.push_back(10);
/*
	std::map<string,unsigned int> m;
	m.insert(make_pair("manaCost",10));
	m.insert(make_pair("manaProfit",15));
	m.insert(make_pair("pointsProfit",10));
	
	actionsDesc_.insert(make_pair("test",m));
	initialManaS_ = 100;
    initialManaT_ = 100;
	FPS = 25;
*/
}

void CConstants::saveToFile()
{
	std::ofstream ofs(utils::PATH_CONSTS.c_str());
	{
		boost::archive::xml_oarchive oa(ofs);	
		oa<<BOOST_SERIALIZATION_NVP(this);
	}
	ofs.close(); 
}

CConstants* CConstants::getInstance()
{
 	if(mInstance_== NULL)
	{	
		std::ifstream ifs(utils::PATH_CONSTS.c_str());
		{
			boost::archive::xml_iarchive ia(ifs);
			ia>>BOOST_SERIALIZATION_NVP(mInstance_);
		}
		ifs.close();
	}
	assert(mInstance_ != NULL);
	
	return mInstance_;
	
}
