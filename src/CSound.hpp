/**
* @author Rafal Malinowski
* @date 2009.12.18
* @version 0.1_draft
* @class CSound CSound.hpp
* @brief klasa CSound bedzie odpowiedzialna za przechowywanie informacji o dzwiekach
*	
*		
*/

#ifndef CSOUND_H
#define CSOUND_H

#include <string>
#include <iostream>
#include "SDL.h"
#include "SDL_mixer.h"
#include "CAudioSystem.hpp"


//#include <boost/smart_ptr.hpp>

using namespace std;
class CSound
{
public:
	///Konstruktor Domyslny
	CSound();
	///Destruktor
	~CSound();
	///
	///Przeladowany konstruktor
	///@param channel kanal w jakim bedzie odtwarzany dzwiek
	///@param nickname pseudonim jakim ma byc przezywany dzwiek (ulatwia prace z dzwiekami)
	///@param filename sciezka do dzwieku ktory ma zostac zaladowany
	///
	CSound(int channel, string nickname, string filename);

	///Licznik ulatwiajacy przypisywanie unikalnego id_ kazdemu dzwiekowi
	static int licznik;

	///Metoda wlaczajaca odgrywanie dzwieku (wykorzystywana wylacznie przez CAudioSystem)
	void Play();
	///Metoda wylaczajaca odgrywanie dzwieku (wykorzystywana wylacznie przez CAudioSystem)
	void Stop();
	///Metoda ustawiajaca kierunek z ktorego bedzie slychac dzwiek, dzieki parametrowi angle_
	void SetPosition();
	///Metoda ustawiajaca kat pod jakim bedzie slychac dzwiek angle_
	void SetAngle (Sint16 angle);
	///Metoda ustawiajaca glosnosc dzwieku
	void SetVolume (int volume);

	///Metoda zwracajaca id_ dzwieku
	///@return id_ dzwieku
	int GetId() const;

	///Metoda zwracajaca channel_ dzwieku
	///@return channel_ dzwieku
	int GetChannel() const;

	///Metoda zwracajaca nickname_ dzwieku
	///@return nickname_ dzwieku
	string GetNickname() const;

	///Metoda zwracajaca angle_ dzwieku
	///@return angle_ dzwieku
	Sint16 GetAngle() const;

	///Metoda zwracajaca glosnosc dzwieku
	///@return volume_ dzwieku
	int GetVolume() const;
private:
	///przechowuje informacje o kacie pod jakim bedzie mozna slyszec dzwiek
	Sint16 angle_;
	///wskaznik do Mix_Chunk przechowujacy informacje o dzwieku
	Mix_Chunk * sound;
	///Unikalny klucz muzyki
	int id_;
	///Nickname muzyki
	string nick_;
	///Kanal w ktorym bedzie odtwarzany dzwiek
	int channel_;

	///glosnosc dzwieku
	int volume_;

};

///Przeladowanie operatora<, potrzebny, aby w CAudioSystem mozna bylo uzywac std::set
bool operator<(const CSound& sound1, const CSound& sound2 );

#endif

//~~CSound.hpp