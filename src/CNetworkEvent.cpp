#include "CNetworkEvent.hpp"
#include "CNetwork.hpp"
//#include "CAudioSystem.hpp" //na chwile
#include "CAuditorium.hpp"
int CNetworkEvent::sqn_ = 0;

void CNetworkEvent::send()
{
	cout<<"CNetworkEvent::send()"<<endl;
	thisSqn_ = sqn_++;
	CNetwork::getInstance()->send(*this);
}

CNetworkEvent::CNetworkEvent()
{
	cout<<"CNetworkEvent::CNetworkEvent()"<<endl;
	thisSqn_ = -1;
}

void CNetworkEvent::execute()
{
	CAuditorium::getInstance()->seatNewStudent(r,c,t);
	CAudioSystem::getInstance()->play_sound("dzien_dobry");
}