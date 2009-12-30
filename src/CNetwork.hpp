/**
* @author Czarek Zawadka
* @date 2009.12.29
* @version 0.1_draft
* 

*/
#ifndef NETWORK_H
#define NETWORK_H

#include <iostream>
#include <sstream>
#include <string>

#include "SDL_net.h"
#include "CSingleton.hpp"
#include "CTimerObserver.hpp"

class CNetwork : public CSingleton<CNetwork>, public CTimerObserver 
{
	friend CSingleton<CNetwork>;

public:
	
	int initNetwork(std::string peerIP, int port = 2010);
	void handleNetwork();
	virtual void refresh(int interval, SDL_TimerID timerIds);

private:

	CNetwork();
	~CNetwork();

	//czesc serwerowa:
	TCPsocket sd_, csd_; /* Socket descriptor, Client socket descriptor */
	IPaddress ip_, *remoteIP_;
//	int quit_, quit2_;
//	char buffer_[1024];
	SDLNet_SocketSet sockSet_;
	
	
	//czesc kliencka
//	IPaddress ipC_;		/* Server address */
//	TCPsocket sdC_;		/* Socket descriptor */
//	char bufferC_[1024];

	bool isClient;
};

#endif