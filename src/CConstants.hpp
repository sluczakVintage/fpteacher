/**\file
* @author Czarek Zawadka
* @date 2010.02.28
* @version 0.6
* @class CConstants CConstants.hpp 
* @brief klasa, singleton, przechowuje stale
* 
* @todo zrobic const co sie tylko da
* @todo rozwiazac problem mozliwego podwojnego tworzenia obiektu tej klasy
* @todo WAZNE dodac rozroznienie opisu zdarzen dla studenta i teachera
*/
#ifndef CCONSTANTS_HPP
#define CCONSTANTS_HPP

#include  "CSingleton.hpp"
#include "boost/tuple/tuple.hpp"
#include <string>
#include <map>
#include <vector>
#include <boost/serialization/nvp.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include "utils.hpp"
#include <fstream>
#include "boost/archive/xml_oarchive.hpp"
#include "boost/serialization/map.hpp" 
#include "boost/serialization/vector.hpp"

using namespace std;

typedef	std::map<string, std::map<string,unsigned int> > AcDesMap;


class CConstants : public CSingleton<CConstants>
{
	friend class CSingleton<CConstants>;
	friend class boost::serialization::access;

public:

	//opis akcji
	//nazwa, manaCost, manaProfit, pointsProfit
	//to raczej odpada, nie chce mi sie pisac serializacji do tuple
	//std::map<string, boost::tuple<unsigned int,unsigned int,unsigned int> > actionsDesc_;
	
	//alternatywna wersja:
	//tu mozna opisac akcje przez wiele numerkow z wektora, ale powinny byc przynajmniej 3
	//std::map<string, std::vector<unsigned int> > actionsDesc_;

	//kolejna alternatywa - bardziej czytelny zapis w xml
	//pierwszys tring to nazwa zdarezenia, potem nazwa parametru i wartosc parametru
	//std::map<string, std::vector<std::pair<string,unsigned int> > actionsDesc_;

	//kolejna alternatywa - bardziej czytelny zapis w xml, szybkie dzia³anie?
	//pierwszys tring to nazwa zdarezenia, potem nazwa parametru i wartosc parametru
	//ka¿da (pod)mapa opisujaca zdarzenie musi miec 4!! parametry: manaCost_; manaProfit_; pointsProfit_; whose_;
	std::map<string, std::map<string,unsigned int> > actionsDesc_;

	unsigned int initialManaS_;
	unsigned int initialManaT_;
	int FPS;
	
	void saveToFile();
	static CConstants* getInstance();

//	static void init();

private:
	
	template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & BOOST_SERIALIZATION_NVP(initialManaS_);
        ar & BOOST_SERIALIZATION_NVP(initialManaT_);
		ar & BOOST_SERIALIZATION_NVP(FPS);
        ar & BOOST_SERIALIZATION_NVP(actionsDesc_);
    }

	static CConstants* mInstance_;
	CConstants();

};
#endif
