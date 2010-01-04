/** @file CNetwork.cpp
* @author Czarek Zawadka
* @date 2009.12.29
* @version 0.1_draft
* 
* @brief CNetwork to wstepna klasa odpowiedzialna za komunikacje sieciowa
*
* @todo przemyslec i zaimplementowac protokol komunikacji sieciowej - jakie obiekty, kiedy i jak przesylac przez siec.
* @todo wywolac handleNetwork() z silnika z zaimplementowanych schedulerem
* @todo zlikwidowac imlementacje CTimerObserver - sluzy tylko do celow demonstracyjnych
* @todo podzielic CNetwork tak, aby dzialalo w niezale�nych w�tkach
*/

#include "CNetwork.hpp"

using namespace std;

//static TCPsocket csd_;/* Socket descriptor, Client socket descriptor */
//static SDLNet_SocketSet sockSet_;
bool CNetwork::stopRecThread_ = true ;
SDLNet_SocketSet CNetwork::sockSet_ = NULL;
queue<CNetwork::Buffer> CNetwork::received_;// = *(new queue<CNetwork::Buffer>); 
TCPsocket CNetwork::csd_ = NULL;

CNetwork::CNetwork()
{

}

CNetwork::~CNetwork()
{
	stopRecThread_ = true;
	recThread_.join();
	SDLNet_TCP_Close(csd_);
}


///W tej metodzie najpierw jest nawiazywane polaczenie z peerIP na porcie 'port', jezeli to sie nie uda 
///rozpoczynane jest nasluchiwanie polaczen przychodzacych na porcie 'port'
///@param peerIP - ip komputera z ktorym chcemy si� po��czy�
///@param port - port TCP na kt�rym maj� by� nas�uchiwane po��czenia od innych
int CNetwork::initNetwork(std::string peerIP,  int port)
{
	if (SDLNet_Init() < 0)
	{
		fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
	}

//czesc kliencka

	/* Resolve the host we are connecting to */
	if (SDLNet_ResolveHost(&ip_, peerIP.c_str(), port) < 0)
	{
		fprintf(stderr, "SDLNet_ResolveHost: %s\n", SDLNet_GetError());
		//exit(EXIT_FAILURE);
	}
  	
	 /* Open a connection with the IP provided (listen on the host's port) */
	if ((csd_ = SDLNet_TCP_Open(&ip_)))
	{
		//kezeli udalo sie otworzyc polaczenie
		printf("initNetwork() %d   %d", ip_.host, ip_.port);
		isClient_ = true;
		sockSet_=SDLNet_AllocSocketSet(1);
		SDLNet_TCP_AddSocket(sockSet_, csd_);
		return 1;
	}
	else
		fprintf(stderr, "SDLNet_TCP_Open: %s\n", SDLNet_GetError());

//~~czesc kliencka


//czesc serwerowa 
	/* Resolving the host using NULL make network interface to listen */
	if (SDLNet_ResolveHost(&ip_, NULL, port) < 0)
	{
		fprintf(stderr, "SDLNet_ResolveHost: %s\n", SDLNet_GetError());
		//exit(EXIT_FAILURE);
	}

	/* Open a connection with the IP provided (listen on the host's port) */
	if (!(sd_ = SDLNet_TCP_Open(&ip_)))
	{
		fprintf(stderr, "SDLNet_TCP_Open: %s\n", SDLNet_GetError());
		//exit(EXIT_FAILURE);
	}
	/* Wait for a connection, send data and term */

	int quit = 0;

		
	while (!quit)
	{
		/* This check the sd if there is a pending connection.
		* If there is one, accept that, and open a new socket for communicating */
		if ((csd_ = SDLNet_TCP_Accept(sd_)))
		{
			/* Get the remote address */
			if ((remoteIP_ = SDLNet_TCP_GetPeerAddress(csd_)))
			{/* Print the address, converting in the host format */
				printf("Host connected: %x %d\n", SDLNet_Read32(&remoteIP_->host), SDLNet_Read16(&remoteIP_->port));
				quit =1;
				SDLNet_TCP_Close(sd_);
			}
			else
				fprintf(stderr, "SDLNet_TCP_GetPeerAddress: %s\n", SDLNet_GetError());
		}	
	}

	isClient_ = false;
//~~czesc serwerowa 

	sockSet_=SDLNet_AllocSocketSet(1);
	SDLNet_TCP_AddSocket(sockSet_, csd_);
	
	return 0;
}
void CNetwork::startRec()
{
	stopRecThread_ = false;
	recThread_ = boost::thread(&CNetwork::receive);
}

void CNetwork::receive()
{
	cout<<"CNetwork::receive()"<<endl;
	while(!stopRecThread_)
	{
		int numready = SDLNet_CheckSockets(sockSet_, 1000/utils::FPS);
		if (numready == -1) 
		{
			printf("SDLNet_CheckSockets: %s  numready: %d\n", SDLNet_GetError(),numready );
		}
		else if (numready) 
		{
			Buffer b;
			if (SDLNet_TCP_Recv(csd_, b.buffer_, MAX_BUFF - 1) > 0)
			{
				received_.push(b);
			}
		}	
	}
}


void CNetwork::refresh(int interval, SDL_TimerID timerIds)
{
	string str;
	stringstream out;
	int i = (CTimer::getInstance()-> getTime()) % 11;
	
	if (i < 4) 
	{
		while (!received_.empty())
		{
			cout /*<<(CTimer::getInstance()-> getTime())/1000.0 */<<" received_.front() "<<sizeof(received_.front().buffer_)<<endl;;
			received_.pop();
		}

	}
	
	out << 2147483645;
	str = out.str();
	Buffer b;
	strcpy(b.buffer_,str.c_str());
//	cout<<"CNetwork::refresh "<<str<<endl;

	//int len = strlen(str.c_str()) + 1;
	int len = sizeof(b.buffer_);
	cout<<"CNetwork::refresh wysylanie: "<<i<<endl;
	for (i; i>0; i--)
	{
/*
		//cout<<(CTimer::getInstance()-> getTime())/1000.0 <<" CNetwork::refresh wysylanie: "<<str <<endl;
		if (SDLNet_TCP_Send(csd_, (void *)str.c_str(), len) < len)
		{
			fprintf(stderr, "SDLNet_TCP_Send: %s\n", SDLNet_GetError());
		}
*/
		if (SDLNet_TCP_Send(csd_, b.buffer_, len) < len)
		{
			fprintf(stderr, "SDLNet_TCP_Send: %s\n", SDLNet_GetError());
		}
	}
}