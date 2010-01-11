/*
* @author Czarek Zawadka
* @date 2010.01.10
* @version 0.1_draft
* @class CSoundNetworkEvent CSoundNetworkEvent.hpp
* @brief CZAREK

*/

#ifndef C_SOUND_NETWORK_EVENT_H	
#define C_SOUND_NETWORK_EVENT_H

/*
#include <iostream>

#include <boost/any.hpp>
//#include <map>
//#include <string>
//#include "CNetwork.hpp"
*/
//#include <boost/archive/text_oarchive.hpp>
//#include <boost/archive/text_oarchive.hpp>

#include <boost/serialization/split_member.hpp>
#include <boost/serialization/nvp.hpp>
//#include <boost/serialization/export.hpp> 
#include "CNetworkEvent.hpp"
#include "CAudioSystem.hpp"

//class CSoundNetworkEvent;

//BOOST_CLASS_EXPORT(CSoundNetworkEvent);

using namespace std;

//class CNetwork;

class CSoundNetworkEvent : public CNetworkEvent
{

	friend class CNetwork;
	friend class boost::serialization::access;

public:

	
	CSoundNetworkEvent();

	CSoundNetworkEvent(int pos, int dist_, string sound);

protected:
		
	int pos_;
	
	int dist_;
	string sound_;

	template<class Archive>
    void save(Archive & ar, const unsigned int version) const
	{
		ar & boost::serialization::base_object<CNetworkEvent>(*this);
		ar & (pos_); 
		ar & (dist_);
		ar & (sound_);
	}
	
	///szablon umozliwiajacy deserializacje klasy
	///@param &ar archiwum z przestrzeni nazw boost::archive
	///@param version pole umozliwiajace wersjonowanie klasy, poki co niewykorzystane
	template<class Archive>
    void load(Archive & ar, const unsigned int version)
    {
		ar & boost::serialization::base_object<CNetworkEvent>(*this);
		ar & (pos_);
		ar & (dist_);
		ar & (sound_);
	}

//	int parameter_;

	virtual void execute();

	BOOST_SERIALIZATION_SPLIT_MEMBER();

	//std::map<boost::any> params_;

};
#endif

