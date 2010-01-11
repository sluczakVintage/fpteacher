/*
* @author Czarek Zawadka
* @date 2010.01.10
* @version 0.1_draft
* @class CNetworkEvent CNetworkEvent.hpp
* @todo przemyslec zrobienie z tego klasy wirtualnej
* @todo poprawic BOOST_CLASS_EXPORT
*/

#ifndef C_NETWORK_EVENT_H	
#define C_NETWORK_EVENT_H

#include <iostream>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/export.hpp> 
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_oarchive.hpp>



//#include <map>
//#include <string>
//#include "CNetwork.hpp"

using namespace std;


//class CNetwork;

class CNetworkEvent
{

	friend class CNetwork;
	friend class boost::serialization::access;

public:

	/*
	int r;
	int c;
	int t;
	int pos;
	int dist;
*/

	CNetworkEvent();
	
	virtual ~CNetworkEvent();

	void send();

protected:

	template<class Archive>
    void save(Archive & ar, const unsigned int version) const
	{
	//	ar & BOOST_SERIALIZATION_NVP(thisSqn_); 
		ar & (thisSqn_); 
	}
	
	///szablon umozliwiajacy deserializacje klasy
	///@param &ar archiwum z przestrzeni nazw boost::archive
	///@param version pole umozliwiajace wersjonowanie klasy, poki co niewykorzystane
	template<class Archive>
    void load(Archive & ar, const unsigned int version)
    {
		//ar & BOOST_SERIALIZATION_NVP(thisSqn_); 
		ar & (thisSqn_); 
	}

	virtual void execute();

	BOOST_SERIALIZATION_SPLIT_MEMBER();


private:
	static int sqn_;
	
	int thisSqn_;

};
#endif

