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

#include <fstream>
#include <iostream>
#include <string>
#include "CSingleton.hpp"
#include "utils.hpp"

using namespace std;

class CLog : public CSingleton<CLog>
{
	friend class CSingleton<CLog>;

public:

	enum stream_type {
		temp=1,
		info=2,
		warning=3,
		error=4};

	///konstruktor domyslny
	CLog();
	///destruktor
	~CLog();

	ofstream info_stream;
	ofstream temp_stream;
	ofstream error_stream;
	ofstream warning_stream;

	bool getError_on_console();
	bool getWarning_on_console();
	bool getTemp_on_console();
	bool getInfo_on_console();

private:
	bool warning_on_console;
	bool error_on_console;
	bool temp_on_console;
	bool info_on_console;

};

namespace logs
{
	//void logs(string text, CLog::stream_type stream);
	void logs(string text, int stream);
}


#endif


//~~log.hpp