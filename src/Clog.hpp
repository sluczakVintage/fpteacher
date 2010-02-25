/** \file
* 
* @author Rafal Malinowski
* @date 2010.02.26
* @version 0.6
* @class CLog CLog.hpp
* @brief klasa CLogic odpowiada za poprawne logowanie
*
*		
*/
#ifndef CLOG
#define CLOG

#include<fstream>
#include <iostream>
#include "CSingleton.hpp"

using namespace std;

class CLog : public CSingleton<CLog>
{
	friend class CSingleton<CLog>;

public:

	///konstruktor domyslny
	CLog();
	///destruktor
	~CLog();
	ofstream cout;


};

#endif

//~~log.hpp