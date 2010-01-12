#include "CNetworkEvent.hpp"
#include "CNetwork.hpp"
//#include "Boost/Serialization/tracking.hpp"

//Licznik utworzonych obiektow
int CNetworkEvent::sqn_ = 0;

//BOOST_CLASS_EXPORT(CNetworkEvent);

//makro likwidujace ostrzezenie o staticach, nie dziala
BOOST_CLASS_TRACKING(CNetworkEvent, boost::serialization::track_never);

//Konstruktor domyslny
CNetworkEvent::CNetworkEvent()
{
	cout<<"CNetworkEvent::CNetworkEvent() tworzenie"<<endl;
	thisSqn_ = -1;
}

//Destruktor wirtualny
CNetworkEvent::~CNetworkEvent()
{
	cout<<"CNetworkEvent::~CNetworkEvent() niszczenie"<<endl;

}

//Metoda wysylajaca obiekt do klasy CNetwork gdzie jest kolejkowany i przesylany
void CNetworkEvent::send()
{
	cout<<"CNetworkEvent::send()"<<endl;
	thisSqn_ = sqn_++;
	CNetwork::getInstance()->send(this);
}

//metoda wolana po zdeserializowaniu obiektu - wykonuje logike zdarzenia
void CNetworkEvent::execute()
{

}

//~~CNetworkEvent.cpp
