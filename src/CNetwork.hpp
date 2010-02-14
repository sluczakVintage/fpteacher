/**\file
* @author Czarek Zawadka
* @date 2009.12.29
* @version 0.9
* @class CNetwork CNetwork.hpp
* @brief CNetwork to klasa odpowiedzialna za komunikacje sieciowa
*
*
* @todo przeniesc logike zdarzen przychodzacych w zupelnie nowa klase
* @todo przemyslec i zaimplementowac protokol komunikacji sieciowej - jakie obiekty, kiedy i jak przesylac przez siec.
* @todo obsluzyc zamykanie polaczenia przez jedna ze stron
* @todo udoskonalic usypianie watkow
* @todo optymalniejsze wykorzystanie sieci
* @todo rzucanie wyjatkow przy przepelnieniu buforow lub przy zerwaniu polaczenia
* @todo poprawic BOOST_CLASS_EXPORT
* @todo dodac wybor bycia studentami/wykladowca
* @todo poprawic zarzadzanie zasobami CNetworkEvent
*/

#ifndef NETWORK_H
#define NETWORK_H

#include <iostream>
#include <sstream>
#include <string>
#include <queue>
#include <boost/thread.hpp>
#include "utils.hpp"
#include "SDL_net.h"
#include "CSingleton.hpp"
#include "CTimer.hpp"
#include "CNetworkEvent.hpp"
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/export.hpp> 
#include <boost/thread/mutex.hpp>

//class CNetworkEvent;

class CNetwork : public CSingleton<CNetwork>//, public CTimerObserver 
{
	friend class CSingleton<CNetwork>;

public:
	
	///inicjalizacja sieci. 
	///@param peerIP - ip komputera z ktorym chcemy sie polaczyc
	///@param port - port TCP na ktorym maja byc nasluchiwane polaczenia od innych
	int initNetwork(std::string peerIP, int port = 20010);
	
	///tu sa kolejkowane obiekty CNetworkEvent do wslania
	void send(CNetworkEvent * cne);
	
	///uruchamia watek ktory odbiera dane z sieci
	void startRec();
	
	//zatrzymuje watek ktory odbiera dane z sieci
	//	void stopRec();

	///uruchamia watek wysylajace dane
	void startSend();
	
	//	void stopSend();
	
	///metoda w ktorej odbywa sie przetwarzanie odebranych danych
	void handleNetwork();

	///@return informcacja czy to my zalozylismy serwer na poczatku polaczenia
	bool getIsClient();

	//metoda zaimplementowana dla przetestowania - wysyla i obrabia odebrane dane
	//virtual void refresh(int interval, SDL_TimerID timerIds);
	
	///rozmiar buforow odbiorczego i nadawczego w KB - cos trzeba bylo ustalic
	const int static MAX_BUFF = 256;

private:
	
	///Domyslny konstruktor
	CNetwork();
	
	///Destruktor zamyka watki i dzialajace polaczenia
	~CNetwork();

	///Metoda w ktorej odbywa sie odbieranie, dziala w oddzielnym watku.
	///jest static po to, aby mozliwe bylo wywolanie  boost::thread(&CNetwork::receiveTh);
	static void receiveTh();
	
	///obiekt mutex synchronizujacy watki
	static boost::mutex mutex;
	
	///metoda uruchamiana w watku wysylajacym dane
	static void sendTh();
	
	//czesc serwerowa:
	///Gniazdo do komunikacji
	static TCPsocket csd_;
	
	///Gniazdo do nasluchiwania polaczen przychodzacych. Jezeli wczesniej udalo sie polaczyc nie jest otwierane.
	///Zamykane po nawiazaniu polaczenia
	TCPsocket sd_ ;

	///IP komputera z ktorym sie polaczylismy, jezeli to on byl serwerem
	IPaddress ip_;
	
	///IP komputera z ktorym sie polaczylismy, jezeli to my bylismy serwerem
	IPaddress *remoteIP_;

	///Zbior gniazdek, sluzy do sprawdzania czy gdzies znajduja sie dane do odebrania
	static SDLNet_SocketSet sockSet_;
	
	///Flaga sluzaca do zatrzymania watku odbierania
	static bool stopRecThread_;

	///Flaga sluzaca do zatrzymania watku wysylania
	static bool stopSendThread_;;
	
	///Flaga oznaczajaca, czy jestesmy klientem/serwerem
	static bool isClient_;

	///Instancja watku w ktorym odbywa sie odbieranie
	boost::thread recThread_;

	///Instancja watku w ktorym odbywa sie wysylanie
	boost::thread sendThread_;

	///Struktura danych wysylanych/odbieranych
	struct Buffer
	{
		//boost::shared_ptr<char *> buffer_; 
		char buffer_[MAX_BUFF];
	//	~Buffer(){cout<<"Buffer niszczenie"<<endl;}
	};

	

	//static queue <boost::shared_ptr<char *>> received_; 
	//static queue <Buffer> received_; 
	
	///Kolejka LIFO odebranych danych 
	static queue <CNetworkEvent *> received_;
	
	///Kolejka LIFO danych do wyslania
	static queue <CNetworkEvent *> toSend_; 

}; 

#endif

//~~CNetwork.hpp
