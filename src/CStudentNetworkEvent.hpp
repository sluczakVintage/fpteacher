/*
* @author Czarek Zawadka
* @date 2010.01.10
* @version 0.1_draft
* @class CStudentNetworkEvent CStudentNetworkEvent.hpp
* @brief klasa przesylajaca informacje o nowych studentach na sali
*
*/

#ifndef C_STUDENT_NETWORK_EVENT_H	
#define C_STUDENT_NETWORK_EVENT_H

//#include <boost/archive/text_oarchive.hpp>
//#include <boost/archive/text_oarchive.hpp>

#include <boost/serialization/split_member.hpp>
#include <boost/serialization/nvp.hpp>
//#include <boost/serialization/export.hpp> 
#include "CNetworkEvent.hpp"


//class CStudentNetworkEvent;

//BOOST_CLASS_EXPORT(CStudentNetworkEvent);

using namespace std;

//class CNetwork;

class CStudentNetworkEvent : public CNetworkEvent
{

	friend class CNetwork;
	friend class boost::serialization::access;

public:
		
	///Konstruktor domyslny
	CStudentNetworkEvent();

	///konstruktor ze wszystkimi waznymi parametrami
	///@param int row - numer rzedu
	///@param int column - numer kolumny
	///@param int type - typ studenta
	CStudentNetworkEvent(int row, int column, int type);

protected:
	///numer rzedu
	int row_;
	///numer kolumny
	int column_;
	///typ studenta
	int type_;

	///szablon umozliwiajacy deserializacje klasy
	///@param &ar archiwum z przestrzeni nazw boost::archive
	///@param version pole umozliwiajace wersjonowanie klasy, poki co niewykorzystane
	template<class Archive>
    void save(Archive & ar, const unsigned int version) const
	{
		ar & boost::serialization::base_object<CNetworkEvent>(*this);
		ar & (row_); 
		ar & (column_);
		ar & (type_);
	}
	
	///szablon umozliwiajacy deserializacje klasy
	///@param &ar archiwum z przestrzeni nazw boost::archive
	///@param version pole umozliwiajace wersjonowanie klasy, poki co niewykorzystane
	template<class Archive>
    void load(Archive & ar, const unsigned int version)
    {
		ar & boost::serialization::base_object<CNetworkEvent>(*this);
		ar & (row_); 
		ar & (column_);
		ar & (type_);
	}

//	int parameter_;

	///metoda wolana po zdeserializowaniu obiektu - wykonuje logike zdarzenia
	virtual void execute();

	///Makro pozwalajace uzywac oddzielnych funkcji do serializacji i deserializacji
	BOOST_SERIALIZATION_SPLIT_MEMBER();

	//std::map<boost::any> params_;

};
#endif

