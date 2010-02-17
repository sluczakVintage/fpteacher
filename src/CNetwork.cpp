/** @file CNetwork.cpp
* @author Cezary Zawadka
* @date 2009.12.29
* @version 0.9
* @brief CNetwork to klasa odpowiedzialna za komunikacje sieciowa
*	
*		
*/

#include "CNetwork.hpp"
#include "CSoundNetworkEvent.hpp"
#include "CStudentNetworkEvent.hpp"

//#include "Boost/Serialization/tracking.hpp"

///flaga do serializacji na podstawie RTTI
BOOST_CLASS_EXPORT(CNetworkEvent);

///flaga do serializacji na podstawie RTTI
BOOST_CLASS_EXPORT(CStudentNetworkEvent);

///flaga do serializacji na podstawie RTTI
BOOST_CLASS_EXPORT(CSoundNetworkEvent);

//BOOST_CLASS_TRACKING(CNetworkEvent, boost::serialization::track_never);
//BOOST_CLASS_TRACKING(CSoundNetworkEvent, boost::serialization::track_never);
//BOOST_CLASS_TRACKING(CStudentNetworkEvent, boost::serialization::track_never);

using namespace std;

//skladowa statyczna klasy CNetwork
bool CNetwork::stopRecThread_;// = true ;

//skladowa statyczna klasy CNetwork
bool CNetwork::stopSendThread_;

//skladowa statyczna klasy CNetwork
//bool CNetwork::isClient_;

//skladowa statyczna klasy CNetwork
SDLNet_SocketSet CNetwork::sockSet_;// = NULL;

//skladowa statyczna klasy CNetwork
TCPsocket CNetwork::csd_ = NULL;

//skladowa statyczna klasy CNetwork
queue <CNetworkEvent *> CNetwork::received_;

//skladowa statyczna klasy CNetwork
queue <CNetworkEvent *> CNetwork::toSend_; 

//skladowa statyczna klasy CNetwork
boost::mutex CNetwork::mutex;

const string CNetwork::TEACHER = "TEACHER";
const string CNetwork::STUDENTS = "STUDENTS";
///Konstruktor domyslny
CNetwork::CNetwork()
{
	stopRecThread_ = true;
	stopSendThread_ = true;
//	isClient_ = false;
}

///Destruktor
CNetwork::~CNetwork()
{
	stopRecThread_ = true;
	recThread_.join();
	stopSendThread_ = true;
	sendThread_.join();
	SDLNet_TCP_Close(csd_);
}


//W tej metodzie najpierw jest nawiazywane polaczenie z peerIP na porcie 'port', jezeli to sie nie uda 
//rozpoczynane jest nasluchiwanie polaczen przychodzacych na porcie 'port'
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
		//jezeli udalo sie otworzyc polaczenie
		printf("initNetwork() %d   %d", ip_.host, ip_.port);
//		isClient_ = true;
		sockSet_=SDLNet_AllocSocketSet(1);
		SDLNet_TCP_AddSocket(sockSet_, csd_);
		string s;
		CLogic::getInstance()->getIsTeacher() ==true ? s = TEACHER: s=STUDENTS;
		if (SDLNet_TCP_Send(csd_, s.c_str(), s.length()) < s.length())
		{
			fprintf(stderr, "SDLNet_TCP_Send: %s\n", SDLNet_GetError());
		}

		startRec();
		startSend();		
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
	int t = 0;
	cout<<"Nasluchiwanie polaczen przychodzacych na porcie: "<<port<<endl;
//	printf("dupa");	
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
				
				Buffer b;
				if (SDLNet_TCP_Recv(csd_, &(b.buffer_), MAX_BUFF) > 0)
				{
					char * c = b.buffer_;
					string s (c);
					if(s.substr(0,TEACHER.length()) == TEACHER)
					{	//gosc po drugiej stronie wybral teacher'a
						CLogic::getInstance()->isTeacher = false;
					}
					else 
					{
						CLogic::getInstance()->isTeacher = true;
					}
				}

				startRec();
				startSend();
			}
			else
				fprintf(stderr, "SDLNet_TCP_GetPeerAddress: %s\n", SDLNet_GetError());
		}	
			CTimer::getInstance()->delay(10);
			if(((t+=10) > 100*1000))
			{
				quit = true;
				cout<<"Nie podlaczono zadnego klienta, uruchamianie trybu gry pojedynczej... "<<endl;
				CTimer::getInstance()->delay(1000);
				break;
			}
			
	}

//	isClient_ = false;
//~~czesc serwerowa 

	sockSet_=SDLNet_AllocSocketSet(1);
	SDLNet_TCP_AddSocket(sockSet_, csd_);

	return 0;
}

///uruchamia watek ktory odbiera dane z sieci
void CNetwork::startRec()
{
	stopRecThread_ = false;
	recThread_ = boost::thread(&CNetwork::receiveTh);
}

///uruchamia watek wysylajace dane
void CNetwork::startSend()
{
	stopSendThread_ = false;
	sendThread_ = boost::thread(&CNetwork::sendTh);
}

//Metoda w ktorej odbywa sie odbieranie, dziala w oddzielnym watku.
//jest static po to, aby mozliwe bylo wywolanie  boost::thread(&CNetwork::receiveTh);
void CNetwork::receiveTh()
{
	
	cout<<"CNetwork::receive()"<<endl;
	while(!stopRecThread_)
	{
		boost::mutex::scoped_lock scoped_lock(mutex);
		{
			CTimer::getInstance()->delay(10);
			int numready = SDLNet_CheckSockets(sockSet_, 1000/utils::FPS);
			if (numready == -1) 
			{
				printf("SDLNet_CheckSockets: %s  numready: %d\n", SDLNet_GetError(),numready );
			}
			else if (numready) 
			{
				Buffer b;
				if (SDLNet_TCP_Recv(csd_, &(b.buffer_), MAX_BUFF) > 0)
				{
					CNetworkEvent * cne;
					char * c = b.buffer_;
					string s (c);
					std::istringstream iss(s);
					boost::archive::text_iarchive ia(iss);
					//ia>>BOOST_SERIALIZATION_NVP(cne);
					ia>>(cne);
					received_.push(cne);

				}
			}	
		}
	}
}

//tu sa kolejkowane obiekty CNetworkEvent do wslania
void CNetwork::send(CNetworkEvent * cne)
{
	cout<<"CNetwork::send()"<<endl;
	if(stopSendThread_ == false)
		toSend_.push(cne);
	else
		delete cne;
}

//metoda uruchamiana w watku wysylajacym dane
void CNetwork::sendTh()
{
	cout<<"CNetwork::send()"<<endl;
	while(!stopSendThread_)
	{
		CTimer::getInstance()->delay(10);
		boost::mutex::scoped_lock scoped_lock(mutex);
		while(!toSend_.empty())
		{
			//int i = toSend_.size();
			cout<<"CNetwork::sendTh()"<<endl;
			Buffer b;
			std::ostringstream oss;
			//boost::archive::xml_oarchive oa(oss);
			boost::archive::text_oarchive oa(oss);
		//	oa<<BOOST_SERIALIZATION_NVP(toSend_.front());
			toSend_;
			oa<<(toSend_.front());
			//b.buffer_=oss.str().c_str();
			strcpy(b.buffer_, oss.str().c_str());
			//const string str =  oss.str();
			int len = sizeof(b.buffer_);
			
			if (SDLNet_TCP_Send(csd_, b.buffer_, len) < len)
			{
				fprintf(stderr, "SDLNet_TCP_Send: %s\n", SDLNet_GetError());
			}
			delete(toSend_.front());
			toSend_.pop();		
		}
	}
}

//metoda w ktorej odbywa sie przetwarzanie odebranych danych
void CNetwork::handleNetwork()
{
		while (!received_.empty())
		{
			//cout<<"CNetwork::handleNetwork() -----------------------------------> odebrano "<<received_.front().thisSqn_<<endl;;
			received_.front()->execute();
			delete(received_.front());
			received_.pop();
		}

}

///@return informcacja czy to my zalozylismy serwer na poczatku polaczenia
/*bool CNetwork::getIsClient()
{
	return isClient_;
}
*/
//~~CNetwork.cpp
