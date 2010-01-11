/**
* @author Rafal Malinowski
* @date 2009.12.18
* @version 0.1_draft
* @class CMusic CMusic.hpp
* @brief klasa CMusic bedzie odpowiedzialna za przechowywanie informacji o muzyce
*	
*		
*/

#ifndef CMUSIC_H
#define CMUSIC_H

#include <string>
#include <iostream>
#include "SDL.h"
#include "SDL_mixer.h"
#include "CAudioSystem.hpp"


#include <boost/smart_ptr.hpp>

using namespace std;
class CMusic
{
public:
	///Konstruktor Domyslny
	CMusic();
	///Destruktor
	~CMusic();

	///Przeladowany konstruktor
	///@param nickname pseudonim jakim ma byc przezywana piosenka (ulatwia prace z muzyka)
	///@param filename sciezka do muzyki ktora ma zostac zaladowana
	CMusic(string nickname, string filename);

	///Licznik ulatwiajacy przypisywanie unikalnego id_ kazdej muzyce
	static int licznik;

	///Metoda wlaczajaca/wstrzumujaca odgrywanie muzyki (wykorzystywana wylacznie przez CAudioSystem)
	void Play_Pause();
	///Metoda wlaczajaca odgrywanie muzyki (wykorzystywana wylacznie przez CAudioSystem)
	void Play();
	///Metoda wstrzymujaca odgrywanie muzyki (wykorzystywana wylacznie przez CAudioSystem)
	void Pause();
	///Metoda wylaczajaca odgrywanie muzyki (wykorzystywana wylacznie przez CAudioSystem)
	void Stop();

	///Metoda zwracajaca id_ muzyki
	///@return id_ muzyki
	int GetId() const;

	///Metoda zwracajaca nickname_ muzyki
	///@return nickname_ muzyki
	string GetNickname() const ;

private:
	///wskaznik do Mix_music przechowujacy informacje o muzyce
	Mix_Music * music;
	///Unikalny klucz muzyki
	int id_;
	///Nickname muzyki
	string nick_;
};

///Przeladowanie operatora<, potrzebny, aby w CAudioSystem mozna bylo uzywac std::set
bool operator<(const CMusic& music1, const CMusic& music2 );

#endif

//~~CMusic.hpp