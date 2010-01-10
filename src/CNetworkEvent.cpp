#include "CNetworkEvent.hpp"
#include "CNetwork.hpp"
int CNetworkEvent::sqn_ = 0;

//BOOST_CLASS_EXPORT(CNetworkEvent);

CNetworkEvent::CNetworkEvent()
{
	cout<<"CNetworkEvent::CNetworkEvent() tworzenie"<<endl;
	thisSqn_ = -1;
}

CNetworkEvent::~CNetworkEvent()
{
	cout<<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>CNetworkEvent::~CNetworkEvent() niszczenie"<<endl;

}

void CNetworkEvent::send()
{
	cout<<"CNetworkEvent::send()"<<endl;
	thisSqn_ = sqn_++;
	CNetwork::getInstance()->send(this);
}

void CNetworkEvent::execute()
{
	/*
	CAuditorium::getInstance()->seatNewStudent(r,c,t);
	CAudioSystem::getInstance()->set_sound_position("dzien_dobry", pos , dist);
	CAudioSystem::getInstance()->play_sound("dzien_dobry");
	*/
}