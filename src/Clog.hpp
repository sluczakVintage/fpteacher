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


	///konstruktor domyslny
	CLog();
	///destruktor
	~CLog();

	void setLoggingOnConsole(bool temp, bool info, bool warning, bool error);

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
	enum stream_type {
	temp=1,
	info=2,
	warning=3,
	error=4};

	void logs(string text, stream_type stream);

}


#endif


//~~log.hpp