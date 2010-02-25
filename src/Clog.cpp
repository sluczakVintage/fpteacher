/**
* 
* @author Rafal Malinowski
* @date 2010.02.26
* @version 0.6
* @class CLog CLog.hpp
* @brief klasa CLogic odpowiada za poprawne logowanie
*		
*/

#include "CLog.hpp"

using namespace std;

///konstruktor domyslny
CLog::CLog()
{

	cout.open("../doc/log.txt", ios::trunc | ios::out);
	cout << "konstruktor CLog" << endl;
}

CLog::~CLog()
{
	cout << "destruktor CLog" << endl;
	cout.close();
}