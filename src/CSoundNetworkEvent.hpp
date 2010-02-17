/**\file
* @author Czarek Zawadka
* @date 2010.01.10
* @version 0.6
* @class CSoundNetworkEvent CSoundNetworkEvent.hpp
* @brief klasa przesylajaca informacje o odtwarzanych dzwiekach
*
* Dziedziczy po CNetworkEvent
* 
* @todo poprawic dzwieki przezstrzenne po sieci
*/

#ifndef C_SOUND_NETWORK_EVENT_H	
#define C_SOUND_NETWORK_EVENT_H


//#include <iostream>
//#include <boost/any.hpp>
//#include <map>
//#include <string>
//#include "CNetwork.hpp"
//#include <boost/archive/text_oarchive.hpp>
//#include <boost/archive/text_oarchive.hpp>

#include <boost/serialization/split_member.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
//#include <boost/serialization/export.hpp> 
#include "CNetworkEvent.hpp"
#include "CAudioSystem.hpp"
#include "CAuditorium.hpp"



using namespace std;

//class CAuditorium;

class CSoundNetworkEvent : public CNetworkEvent
{

	friend class CNetwork;
	friend class boost::serialization::access;

public:

	///kostruktor domyslny, potrzebny do serializacji i deserializacji
	CSoundNetworkEvent();
	
	///konstruktor ze wszystkimi waznymi parametrami
	///@param pos - pozycja dzwieku - kat
	///@param dist - dystans od sluchajacego
	///@param sound nazwa dzwieku
	CSoundNetworkEvent(int col, int row, string sound);

protected:
		
	///pozycja dzwieku - kat
	int row_;
	
	///dystans od sluchajacego
	int col_;
	
	///nazwa dzwieku
	string sound_;

	///szablon umozliwiajacy deserializacje klasy
	///@param ar archiwum z przestrzeni nazw boost::archive
	///@param version pole umozliwiajace wersjonowanie klasy, poki co niewykorzystane
	template<class Archive>
    void save(Archive & ar, const unsigned int version) const
	{
		ar & BOOST_SERIALIZATION_NVP(boost::serialization::base_object<CNetworkEvent>(*this));
		
		ar & BOOST_SERIALIZATION_NVP(col_); 
		ar & BOOST_SERIALIZATION_NVP(row_);
		ar & BOOST_SERIALIZATION_NVP(sound_);
		
		//ar & (col_); 
		//ar & (row_);
		//ar & (sound_);
	
	}
	
	///szablon umozliwiajacy deserializacje klasy
	///@param ar archiwum z przestrzeni nazw boost::archive
	///@param version pole umozliwiajace wersjonowanie klasy, poki co niewykorzystane
	template<class Archive>
    void load(Archive & ar, const unsigned int version)
    {
		ar & BOOST_SERIALIZATION_NVP(boost::serialization::base_object<CNetworkEvent>(*this));
		
		ar & BOOST_SERIALIZATION_NVP(col_);
		ar & BOOST_SERIALIZATION_NVP(row_);
		ar & BOOST_SERIALIZATION_NVP(sound_);
		
		//ar & (col_); 
		//ar & (row_);
		//ar & (sound_);
	}

	///metoda wolana po zdeserializowaniu obiektu - wykonuje logike zdarzenia
	virtual void execute();

	///Makro pozwalajace uzywac oddzielnych funkcji do serializacji i deserializacji
	BOOST_SERIALIZATION_SPLIT_MEMBER();

	//std::map<boost::any> params_;

};
#endif



//~~CSoundNetworkEvent.hpp
