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
#include <sstream>
#include <iostream>
#include <string>
#include "CSingleton.hpp"
#include "utils.hpp"
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>

using namespace std;

class CLog : public CSingleton<CLog>
{
	friend class CSingleton<CLog>;

public:


	///konstruktor domyslny
	CLog();
	///destruktor
	~CLog();

	/// metoda ustalajaca jakie informacje maja byc wypisywane na console
	/// @param temp gdy chcemy aby wiadomosci typu temp byly wypisywane na console
	/// @param info gdy chcemy aby wiadomosci typu info byly wypisywane na console
	/// @param warning gdy chcemy aby wiadomosci typu warning byly wypisywane na console
	/// @param error gdy chcemy aby wiadomosci typu error byly wypisywane na console
	void setLoggingOnConsole(bool temp, bool info, bool warning, bool error);

	/// strumien odpowiedzialny za zapis do pliku wiadomosci typu info
	ofstream info_stream;
	/// strumien odpowiedzialny za zapis do pliku wiadomosci typu temp
	ofstream temp_stream;
	/// strumien odpowiedzialny za zapis do pliku wiadomosci typu error
	ofstream error_stream;
	/// strumien odpowiedzialny za zapis do pliku wiadomosci typu warning
	ofstream warning_stream;
	/// pomocniczy strumien
	stringstream sss;

	/// metoda zwracajaca wskaznik na strumien sss, pewnie nie bedzie wykorzystywana
	stringstream * returnStream();
	/// metoda mowiaca czy wiadomosci typu error maja byc wypisywane na console
	bool getError_on_console();
	/// metoda mowiaca czy wiadomosci typu warning maja byc wypisywane na console
	bool getWarning_on_console();
	/// metoda mowiaca czy wiadomosci typu temp maja byc wypisywane na console
	bool getTemp_on_console();
	/// metoda mowiaca czy wiadomosci typu info maja byc wypisywane na console
	bool getInfo_on_console();

	boost::mutex mutex_;

private:
	/// flaga mowiaca czy informacje typu warning maja byc wypisywane na console
	bool warning_on_console;
	/// flaga mowiaca czy informacje typu error maja byc wypisywane na console
	bool error_on_console;
	/// flaga mowiaca czy informacje typu temp maja byc wypisywane na console
	bool temp_on_console;
	/// flaga mowiaca czy informacje typu info maja byc wypisywane na console
	bool info_on_console;
	

};

namespace logging
{
	/// enum ulatwiajacy prace z logowaniem
	enum stream_type {
	TEMP=1,
	INFO=2,
	WARNING=3,
	ERR=4};

	/// glowna funkcja sluzaca logowaniu
	/// @param text tekst jaki ma zostac zalogowany
	/// @param stream rodzaj logu wybrany z enuma typu stream_type (TEMP, INFO, WARNING lub ERR)
	void logs(string text, stream_type stream);

}

namespace stream
{
	static stringstream ss(stringstream::in | stringstream::out);
}

#endif


//~~log.hpp