#include "CSoundNetworkEvent.hpp"
//#include "Boost/Serialization/tracking.hpp"
//BOOST_CLASS_EXPORT(CSoundNetworkEvent);

//makro likwidujace ostrzezenie o staticach, nie dziala
BOOST_CLASS_TRACKING(CSoundNetworkEvent, boost::serialization::track_never);

///Konstruktor domyslny
CSoundNetworkEvent::CSoundNetworkEvent()
{

}

//Destruktor wirtualny
CSoundNetworkEvent::CSoundNetworkEvent(int pos, int dist, string sound)
	: pos_(pos), dist_(dist), sound_(sound)
{

}

//metoda wolana po zdeserializowaniu obiektu - wykonuje logike zdarzenia
void CSoundNetworkEvent::execute()
{
		CAudioSystem::getInstance()->set_sound_position("dzien_dobry", pos_ , dist_);
		CAudioSystem::getInstance()->play_sound(sound_);
}

//~~CSoundNetworkEvent.cpp
