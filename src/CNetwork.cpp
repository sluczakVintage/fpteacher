#include "CNetwork.hpp"


using namespace std;

CNetwork::CNetwork()
{

}

CNetwork::~CNetwork()
{
	SDLNet_TCP_Close(csd_);
}
	
int CNetwork::initNetwork(std::string peerIP,  int port)
{
	if (SDLNet_Init() < 0)
	{
		fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
		//exit(EXIT_FAILURE);
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
		isClient = true;
		sockSet_=SDLNet_AllocSocketSet(1);
		SDLNet_TCP_AddSocket(sockSet_, csd_);
		return 1;
	}
	else
		fprintf(stderr, "SDLNet_TCP_Open: %s\n", SDLNet_GetError());
		//exit(EXIT_FAILURE);

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

	isClient = false;
//~~czesc serwerowa 

	sockSet_=SDLNet_AllocSocketSet(1);
	SDLNet_TCP_AddSocket(sockSet_, csd_);
	
	return 0;
}

void CNetwork::handleNetwork()
{
	int numready = SDLNet_CheckSockets(sockSet_, 0);
	if (numready == -1) 
	{
		printf("SDLNet_CheckSockets: %s  numready: %d\n", SDLNet_GetError(),numready );
		// most of the time this is a system error, where perror might help you.
		//perror("SDLNet_CheckSockets");
	}
	else if (numready) 
	{
//	printf("There are %d sockets with activity!\n", numready);
		char buffer[1024];
		if (SDLNet_TCP_Recv(csd_, buffer, 1024) > 0)
		{
			printf("Client say: %s\n", buffer);
		}
	}	

	cout<<" CNetwork::handleNetwork() "<<endl;
}

void CNetwork::refresh(int interval, SDL_TimerID timerIds)
{
	string str;
	stringstream out;
	out <<rand();
	str = out.str();
	str += " wysylanie:";
	cout<<"CNetwork::refresh "<<str<<endl;
//	char bufferC[]= str.c_str();
/*	
	TCPsocket tcpS;
	if(isClient)
		tcpS = sdC_;
	else
		tcpS = csd_;
*/
	int len = strlen(str.c_str()) + 1;

	if (SDLNet_TCP_Send(csd_, (void *)str.c_str(), len) < len)
	{
		fprintf(stderr, "SDLNet_TCP_Send: %s\n", SDLNet_GetError());
	}
	this->handleNetwork();
	//CNetwork::getInstance()->handleNetwork();
}