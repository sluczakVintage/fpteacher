/*
* @author Czarek Zawadka
* @date 2010.01.10
* @version 0.1_draft
* 

*/

#ifndef C_NETWORK_EVENT_H	
#define C_NETWORK_EVENT_H

#include <iostream>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/nvp.hpp>
//#include "CNetwork.hpp"

using namespace std;


//class CNetwork;

class CNetworkEvent
{

	friend class CNetwork;
	friend class boost::serialization::access;

public:

	CNetworkEvent();

	void send();

private:
	template<class Archive>
    void save(Archive & ar, const unsigned int version) const
	{
		ar & BOOST_SERIALIZATION_NVP(thisSqn_); 
	}
	
	///szablon umo¿liwiajacy deserializacje klasy
	///@param &ar archiwum z przestrzeni nazw boost::archive
	///@param version pole umozliwiajace wersjonowanie klasy, poki co niewykorzystane
	template<class Archive>
    void load(Archive & ar, const unsigned int version)
    {
		ar & BOOST_SERIALIZATION_NVP(thisSqn_); 
	}

//	int parameter_;

	virtual void execute();

	BOOST_SERIALIZATION_SPLIT_MEMBER();

	static int sqn_;
	
	int thisSqn_;

};
#endif