/**\file
* @author Czarek Zawadka
* @date 2010.01.10
* @version 0.6
* @class CNetworkEvent CNetworkEvent.hpp 
* @brief klasa bazowa zdarzen przesylanych przez siec.
*
* Klasa bazowa zdarzenia sieciowego. Implmentuje szablony funkcji save i load z boost::serialization. 
* Obiekt klasy jest serializowany w CNetwork, po drugiej stronie sieci jest deserializowany i 
* wywolywana jest metoda execute();
* 
* @todo przemyslec zrobienie z tego klasy wirtualnej
* @todo poprawic BOOST_CLASS_EXPORT
* @todo powalczyc z Boost/Serialization/tracking
*
*/

#ifndef C_NETWORK_EVENT_H	
#define C_NETWORK_EVENT_H

#include <iostream>
//naglowki boost
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/export.hpp> 
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

using namespace std;

class CNetworkEvent
{

	friend class CNetwork;
	friend class boost::serialization::access;

public:

	///Konstruktor domyslny
	CNetworkEvent();
	
	///Destruktor wirtualny
	virtual ~CNetworkEvent();

	///Metoda wysylajaca obiekt do klasy CNetwork gdzie jest kolejkowany i przesylany
	void send();

protected:

	///szablon umozliwiajacy deserializacje klasy
	///@param &ar archiwum z przestrzeni nazw boost::archive
	///@param version pole umozliwiajace wersjonowanie klasy, poki co niewykorzystane
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
	

	///metoda wolana po zdeserializowaniu obiektu - wykonuje logike zdarzenia
	virtual void execute();

	///Makro pozwalajace uzywac oddzielnych funkcji do serializacji i deserializacji
	BOOST_SERIALIZATION_SPLIT_MEMBER();


private:

	///Licznik utworzonych obiektow
	static int sqn_;
	
	///Numer sekwencyjny tego obiektu
	int thisSqn_;

};
#endif

//~~CNetworkEvent.hpp
