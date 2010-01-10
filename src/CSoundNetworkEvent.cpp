#include "CSoundNetworkEvent.hpp"

//BOOST_CLASS_EXPORT(CSoundNetworkEvent);

CSoundNetworkEvent::CSoundNetworkEvent()
{

}

CSoundNetworkEvent::CSoundNetworkEvent(int pos, int dist, string sound)
	: pos_(pos), dist_(dist), sound_(sound)
{

}

void CSoundNetworkEvent::execute()
{
		CAudioSystem::getInstance()->set_sound_position("dzien_dobry", pos_ , dist_);
}
