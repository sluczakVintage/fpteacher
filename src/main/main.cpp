//#include "globals.hpp"
/*
#include <vld.h>
#define _CRTDBG_MAP_ALLOC
#define _CRTDBG_MAPALLOC 
#include <stdlib.h>
#include <crtdbg.h>
*/
#include <iostream>
#include "CEngine.hpp"
#include "CNetwork.hpp"
//#include <fstream>
//#include <boost/archive/text_oarchive.hpp>
//#include <boost/archive/text_iarchive.hpp>
//#include <boost/archive/text_iarchive.hpp>
//#include <boost/archive/text_oarchive.hpp>

using namespace std;
/*
class Ctod :public CTimerObserver{
public:
	virtual void refresh(int interval, SDL_TimerID timerIds)
	{
		cout<<"Ctod::refresh() "<<endl;// CNetwork::getInstance()->handleNetwork();
	}		
	virtual void refresh();
};
*/
int main(int argc, char *argv[])
{
	string s;
	cout<<"czy uruchomic rozgrywke sieciowa? T/N\n>";
	cin>>s;
	if(s=="T" || s == "t")
	{
		cout<<"podaj adres sieciowy komputera z ktorym chcesz sie polaczyc lub wpisz 0 dla localhost\n>";
		cin>>s;

//		cout<<"podaj adres sieciowy komputera z ktorym chcesz sie polaczyc lub wpisz 0 dla localhost\n>";
//		cin>>s;
		if(s=="0")
			CNetwork::getInstance()->initNetwork("127.0.0.1");
		else
			CNetwork::getInstance()->initNetwork(s.c_str());

		CNetwork::getInstance()->startRec();
		CNetwork::getInstance()->startSend();
//		CTimer::getInstance()->addObserver(*(CNetwork::getInstance()),1500);		
	}
	CEngine::getInstance()->init();
	//tu odbywa sie parsowanie pliku xml i inicjalizacja CAuditorium
	//CAuditorium::getInstance()->initFromXml();
	//a tu zapisanie
	//CAuditorium::getInstance()->saveToXml();
	
//	cout<<"przed:  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<"<<CTimer::getInstance()->getTime()<<endl;
	//std::ofstream ofs;

//	ofs._Filebuffer._Myfile._base;
//	ofs.close();
//	std::ostream o = new ostream();
	/*boost::archive::xml_oarchive oa(ofs);
	CAuditorium * ca = CAuditorium::getInstance();
	oa<<BOOST_SERIALIZATION_NVP(ca);
	ofs.close();
*/

/*	
	struct Buffer
	{
		Buffer(){cout<<"tworze";}
		~Buffer(){cout<<"nieszcze";};<x
		char * buffer_;
	};
	char * charprt;
	{

		//boost::shared_ptr<Buffer> p(new Buffer());
		//p->buffer_ = new char [100];
		//charprt = p->buffer_;
		charprt =new char [100];
		boost::shared_ptr<char *> scp (&charprt);
		//charprt = &(*scp);

		cout<<"charprt: "<<charprt<<endl<<"*scp: "<<*scp<<endl;
	}
*/
	//new (


	CEngine::getInstance()->start(); 
//	CAuditorium::getInstance()->saveToXml();
	CEngine::getInstance()->end();
	CEngine::destroyInstance();

	cout << "elo";
	system("pause");
	_CrtDumpMemoryLeaks();
	return 0;
}
