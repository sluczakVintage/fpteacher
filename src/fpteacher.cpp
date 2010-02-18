#if ( defined(_WIN32)  && defined(_DEBUG) )
#include <vld.h>
#endif

#include "CLogic.hpp"
#include <iostream>
#include "CEngine.hpp"
#include "CNetwork.hpp"
using namespace std;


int main(int argc, char *argv[])
{
	string siec;
	string kto;
	string add;
	cout<<"Podaj kim chcesz grac s/t\n>";
	cin>>kto;
	if(kto=="T" || kto=="t")
		CLogic::getInstance()->prefIsTeacher_ = true;
	else
		CLogic::getInstance()->prefIsTeacher_ = false;

	cout<<"Czy uruchomic rozgrywke sieciowa? T/N\n>";
	cin>>siec;	

	if(siec=="T" || siec == "t")
	{
		cout<<"Podaj adres sieciowy IPv4 komputera z ktorym chcesz sie polaczyc lub wpisz 0 dla localhost\n>";
		cin>>add;

		if(add=="0")
			CNetwork::getInstance()->initNetwork("127.0.0.1");
		else
			CNetwork::getInstance()->initNetwork(add.c_str());
		
	}
	else
	{
		CLogic::getInstance()->init(CLogic::getInstance()->prefIsTeacher_);
	}
	
	CEngine::getInstance()->init();
	CEngine::getInstance()->start(); 

	CEngine::getInstance()->end();
	
	CEngine::destroyInstance();
	CNetwork::destroyInstance();
	CTimer::destroyInstance();
	return 0;
}
