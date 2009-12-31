/**
* @author Czarek Zawadka
* @date 2009.12.29
* @version 0.1_draft
* 
* @brief CNetwork to wstepna klasa odpowiedzialna za komunikacje sieciowa
*
* @todo przemyslec i zaimplementowac protokol komunikacji sieciowej - jakie obiekty, kiedy i jak przesylac przez siec.
* @todo wywolac handleNetwork() z silnika z zaimplementowanych schedulerem
* @todo zlikwidowac imlementacje CTimerObserver - sluzy tylko do celow demonstracyjnych
* @todo podzielic CNetwork tak, aby dzialalo w niezale¿nych w¹tkach
*/

#ifndef NETWORK_H
#define NETWORK_H

#include <iostream>
#include <sstream>
#include <string>
#include <queue>
#include <boost/random.hpp>
#include <boost/thread.hpp>

#include "utils.hpp"
#include "SDL_net.h"
#include "CSingleton.hpp"
#include "CTimerObserver.hpp" 
//#include "CTimer.hpp"

class CNetwork : public CSingleton<CNetwork>, public CTimerObserver 
{
	friend CSingleton<CNetwork>;

public:
	
	int initNetwork(std::string peerIP, int port = 2010);
	
	void send(){};
	void startRec();
	void stopRec();

	void handleNetwork(){};
	virtual void refresh(int interval, SDL_TimerID timerIds);
	
	const int static MAX_BUFF = 1024;
private:

	CNetwork();
	~CNetwork();
	//static
	static void receive();

	//czesc serwerowa:
	//static
	static TCPsocket csd_;/* Socket descriptor, Client socket descriptor */
	TCPsocket sd_ ;
	IPaddress ip_, *remoteIP_;

	//static
	static SDLNet_SocketSet sockSet_;
	//static
	static bool stopRecThread_;
	bool isClient_;

	boost::thread recThread_;
	struct Buffer
	{
		char buffer_[MAX_BUFF];
	};

	//static 
	static queue <Buffer> received_; 

}; 

#endif