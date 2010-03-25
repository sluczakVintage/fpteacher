#if ( defined(_WIN32)  && defined(_DEBUG) )
#include <vld.h>
#endif

#include "CLogic.hpp"
#include <iostream>
#include "CEngine.hpp"
#include "CNetwork.hpp"
//#include <stringstream>
//include "CConstants.hpp"
//#include "CTestAction.hpp"
//#include <boost/bind.hpp>

using namespace std;


int main(int argc, char *argv[])
{
//	stringstream 
//	CConstants * cc =CConstants::getInstance();
//	cout<<typeid(*cc).name()<<"\n"<<typeid(typeid(*cc).name()).name()<<endl;
	//cout<<typeid(boost::bind()).name()<<endl;
	//boost::bind(&(CTestAction::create));
//	CTestAction cta;

	///FESTER: PORWALEM TWOJ KOD, JESLI CHCESZ GO JESZCZE KIEDYS ZOBACZYC, ZAJRZYJ DO CENGINE::INIT :D :D
	/// ZROBILEM TO PO TO, ZEBY CLOG ZAINICJOWAC TAM BEZ WYDRUKOW INFO, mam nadzieje, ze mi wybaczysz ;]
	/// Nic nie zmienilem oczywiscie w kodzie
	
	
	CEngine::getInstance()->init();
	CEngine::getInstance()->start(); 

	CEngine::getInstance()->end();
	

	CEngine::destroyInstance();
	CNetwork::destroyInstance();
	CTimer::destroyInstance();
//	CConstants::getInstance()->actionsDesc_.insert(

/*	std::map<string,unsigned int> m;
	m.insert(make_pair("manaCost",10));
	m.insert(make_pair("manaProfit",15));
	m.insert(make_pair("pointsProfit",10));
	
	CConstants::getInstance()->actionsDesc_.insert(make_pair("test",m));

	CConstants::getInstance()->saveToFile();
*/
	return 0;
}
