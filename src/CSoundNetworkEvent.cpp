#include "CSoundNetworkEvent.hpp"
//#include "CAuditorium.hpp"
//#include "Boost/Serialization/tracking.hpp"

//BOOST_CLASS_EXPORT(CSoundNetworkEvent);

//makro likwidujace ostrzezenie o staticach, nie dziala
BOOST_CLASS_TRACKING(CSoundNetworkEvent, boost::serialization::track_never);

///Konstruktor domyslny
CSoundNetworkEvent::CSoundNetworkEvent()
{

}

//Destruktor wirtualny
CSoundNetworkEvent::CSoundNetworkEvent(int row, int col, string sound)
	: col_(col), row_(row), sound_(sound)
{
  
}

//metoda wolana po zdeserializowaniu obiektu - wykonuje logike zdarzenia
void CSoundNetworkEvent::execute()
{
	std::pair<int,int> sp = CAuditorium::getInstance()->getFieldCoord(row_,col_);
	CAudioSystem::getInstance()->set_sound_position("dzien_dobry", col_ , row_);
	CAudioSystem::getInstance()->play_sound(sound_);
}

//~~CSoundNetworkEvent.cpp
