/**
* @author Czarek Zawadka
* @date 2009.12.29
* @version 0.1_draft
* @class CNetwork CNetwork.hpp
* @brief CNetwork to wstepna klasa odpowiedzialna za komunikacje sieciowa
*
* @todo przemyslec i zaimplementowac protokol komunikacji sieciowej - jakie obiekty, kiedy i jak przesylac przez siec.
* @todo wywolac handleNetwork() z silnika z zaimplementowanych schedulerem
* @todo zlikwidowac imlementacje CTimerObserver - sluzy tylko do celow demonstracyjnych
* @todo zaimplementowac prosty protokol sieciowy - wazne w momencie rozpoczynania rozgrywki
* @todo obsluzyc zamykanie polaczenia przez jedna ze stron
* @todo udoskonalic usypianie watkow
* @todo optymalniejsze wykorzystanie sieci
* @todo rzucanie wyjatkow przy przepelnieniu buforow lub przy zerwaniu polaczenia
* @todo poprawic BOOST_CLASS_EXPORT
*/

#ifndef NETWORK_H
#define NETWORK_H

//#include <iostream>
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




//class CNetworkEvent;

class CNetwork : public CSingleton<CNetwork>//, public CTimerObserver 
{
	friend CSingleton<CNetwork>;

public:
	
	///inicjalizacja sieci. 
	///@param peerIP - ip komputera z ktorym chcemy siê po³¹czyæ
	///@param port - port TCP na ktorym maj¹ byæ nas³uchiwane po³¹czenia od innych
	int initNetwork(std::string peerIP, int port = 20010);
	
	///tu beda wysylane dane
	void send(CNetworkEvent * cne);
	
	///uruchamia w¹tek ktory odbiera dane z sieci
	void startRec();
	
	///zatrzymuje watek ktory odbiera dane z sieci
//	void stopRec();

	void startSend();

//	void stopSend();
	///metoda w ktorej odbywaæ siê bedzie obrabianie odebranych danych
	void handleNetwork();

	///metoda zaimplementowana dla przetestowania - wysyla i obrabia odebrane dane
	//virtual void refresh(int interval, SDL_TimerID timerIds);
	
	///rozmiar buforow odbiorczego i nadawczego w KB - cos trzeba bylo ustalic
	const int static MAX_BUFF = 256;

private:
	
	///Domyœlny konstruktor
	CNetwork();
	
	///Destruktor zamyka watki i dzialajace polaczenia
	~CNetwork();

	///Metoda w ktorej odbywa sie odbieranie, dziala w oddzielnym watku.
	///jest static po to, aby mozliwe bylo wywolanie  boost::thread(&CNetwork::receiveTh);
	static void receiveTh();
	
	
	static void sendTh();
	
	//czesc serwerowa:
	///Gniazdo do komunikacji
	static TCPsocket csd_;
	
	///Gniazdo do nasluchiwania polaczen przychodzacych. Je¿eli wczesniej udalo siê po³¹czyæ nie jest otwierane.
	///Zamykane po nawi¹zaniu po³¹czenia
	TCPsocket sd_ ;

	///IP komputera z ktorym sie polaczylismy, jezeli to on byl serwerem
	IPaddress ip_;
	
	///IP komputera z ktorym sie polaczylismy, jezeli to my bylismy serwerem
	IPaddress *remoteIP_;

	///Zbior gniazdek, sluzy do sprawdzania czy gdzies znajduja sie dane do odebrania
	static SDLNet_SocketSet sockSet_;
	
	///Flaga sluzaca do zatrzymania watku
	static bool stopRecThread_;

	static bool stopSendThread_;;
	///Flaga oznaczajaca, czy jestesmy klientem/serwerem
	bool isClient_;

	///Instancja watku w ktorym odbywa sie odbieranie
	boost::thread recThread_;
	boost::thread sendThread_;
	///Struktura danych wysylanych/odbieranych

	struct Buffer
	{
		//boost::shared_ptr<char *> buffer_; 
		char buffer_[MAX_BUFF];
	//	~Buffer(){cout<<"Buffer niszczenie"<<endl;}
	};

	///Kolejka LIFO odebranych danych 

	//static queue <boost::shared_ptr<char *>> received_; 
	//static queue <Buffer> received_; 
	static queue <CNetworkEvent *> received_;
	static queue <CNetworkEvent *> toSend_; 

}; 



#endif