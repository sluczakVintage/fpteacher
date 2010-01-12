#if ( defined(_WIN32)  && defined(_DEBUG) )
#include <vld.h>
#endif

#include <iostream>
#include "CEngine.hpp"
#include "CNetwork.hpp"

using namespace std;


int main(int argc, char *argv[])
{
	string s;
	cout<<"Czy uruchomic rozgrywke sieciowa? T/N\n>";
	cin>>s;
	if(s=="T" || s == "t")
	{
		cout<<"Podaj adres sieciowy IPv4 komputera z ktorym chcesz sie polaczyc lub wpisz 0 dla localhost\n>";
		cin>>s;

		if(s=="0")
			CNetwork::getInstance()->initNetwork("127.0.0.1");
		else
			CNetwork::getInstance()->initNetwork(s.c_str());
		
	}

	CEngine::getInstance()->init();
	CEngine::getInstance()->start(); 

	CEngine::getInstance()->end();

	CEngine::destroyInstance();
	CNetwork::destroyInstance();
	CTimer::destroyInstance();
	return 0;
}
