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

	//temp_stream.open((utils::PATH_LOGS+"temp_log.txt").c_str() , ios::trunc | ios::out);
	//error_stream.open((utils::PATH_LOGS+"error_log.txt").c_str() , ios::trunc | ios::out);
	//info_stream.open((utils::PATH_LOGS+"info_log.txt").c_str() , ios::trunc | ios::out);

	temp_stream.open("../doc/logs/temp_log.txt" , ios::trunc | ios::out);
	error_stream.open("../doc/logs/error_log.txt" , ios::trunc | ios::out);
	info_stream.open("../doc/logs/info_log.txt" , ios::trunc | ios::out);
	warning_stream.open("../doc/logs/warning_log.txt" , ios::trunc | ios::out);

	warning_stream << "warning stream" << endl;
	temp_stream << "temp stream" << endl;
	error_stream << "error stream" << endl;
	info_stream << "info stream" << endl;
	cout << "konstruktor CLog" << endl;
	warning_on_console=true;
	error_on_console=true;
	info_on_console=true;
	temp_on_console=true;
}

CLog::~CLog()
{
	cout << "destruktor CLog" << endl;
	temp_stream.close();
	error_stream.close();
	info_stream.close();
	warning_stream.close();
}
bool CLog::getError_on_console()
{
	return error_on_console;
}

bool CLog::getWarning_on_console()
{
	return warning_on_console;
}

bool CLog::getTemp_on_console()
{
	return temp_on_console;
}

bool CLog::getInfo_on_console()
{
	return info_on_console;
}

void CLog::setLoggingOnConsole(bool temp, bool info, bool warning, bool error)
{
	temp_on_console=temp;
	info_on_console=info;
	warning_on_console=warning;
	error_on_console=error;
}

void logs::logs(string text, stream_type stream)
{
	switch(stream)
	{
	case 1: //temp
		CLog::getInstance()->temp_stream << text << endl;
		if(CLog::getInstance()->getTemp_on_console()) cout << text << endl;
	case 2: //info
		CLog::getInstance()->info_stream << text << endl;
		if(CLog::getInstance()->getInfo_on_console()) cout << text << endl;
	case 3: //warning
		CLog::getInstance()->warning_stream << text << endl;
		if(CLog::getInstance()->getWarning_on_console()) cout << text << endl;
	case 4: //error
		CLog::getInstance()->error_stream << text << endl;
		if(CLog::getInstance()->getError_on_console()) cout << text << endl;
	default:
		cout << "zly enum" << endl;
	}
}
