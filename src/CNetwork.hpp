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
*
*
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
	
	///inicjalizacja sieci. 
	///@param peerIP - ip komputera z ktorym chcemy siê po³¹czyæ
	///@param port - port TCP na którym maj¹ byæ nas³uchiwane po³¹czenia od innych
	int initNetwork(std::string peerIP, int port = 2010);
	
	///tu beda wysylane dane
	void send(){};
	
	///uruchamia w¹tek który odbiera dane z sieci
	void startRec();
	
	///zatrzymuje watek ktory odbiera dane z sieci
	void stopRec();

	///metoda w której odbywaæ siê bedzie obrabianie odebranych danych
	void handleNetwork(){};

	///metoda zaimplementowana dla przetestowania - wysyla i obrabia odebrane dane
	virtual void refresh(int interval, SDL_TimerID timerIds);
	
	///rozmiar buforow odbiorczego i nadawczego w KB - cos trzeba bylo ustalic
	const int static MAX_BUFF = 65536;

private:
	
	///Domyœlny konstruktor
	CNetwork();
	
	///Destruktor zamyka watki i dzialajace polaczenia
	~CNetwork();

	///Metoda w ktorej odbywa sie odbieranie, dziala w oddzielnym watku.
	///jest static po to, aby mozliwe bylo wywolanie  boost::thread(&CNetwork::receive);
	static void receive();

	//czesc serwerowa:
	///Gniazdo do komunikacji
	static TCPsocket csd_;
	
	///Gniazdo do nasluchiwania polaczen przychodzacych. Je¿eli wczesniej udalo siê po³¹czyæ nie jest otwierane.
	///Zamykane po nawi¹zaniu po³¹czenia
	TCPsocket sd_ ;

	///IP komputera z ktorym sie polaczylismy, jezeli to on byl serwerem
	IPaddress ip_,
	
	///IP komputera z ktorym sie polaczylismy, jezeli to my bylismy serwerem
	IPaddress *remoteIP_;

	///Zbior gniazdek, sluzy do sprawdzania czy gdzies znajduja sie dane do odebrania
	static SDLNet_SocketSet sockSet_;
	
	///Flaga sluzaca do zatrzymania watku
	static bool stopRecThread_;

	///Flaga oznaczajaca, czy jestesmy klientem/serwerem
	bool isClient_;

	///Instancja watku w ktorym odbywa sie odbieranie
	boost::thread recThread_;
	
	///Struktura danych wysylanych/odbieranych
	struct Buffer
	{
		char buffer_[MAX_BUFF];
	};

	///Kolejka LIFO odebranych danych 
	static queue <Buffer> received_; 

}; 

#endif