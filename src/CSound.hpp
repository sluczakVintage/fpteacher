/**\file
* @author Rafal Malinowski
* @date 2009.12.18
* @version 0.6
* @class CSound CSound.hpp
* @brief klasa CSound bedzie odpowiedzialna za przechowywanie informacji o dzwiekach
*	
*		
*/

#ifndef CSOUND_H
#define CSOUND_H

#include <string>
#include <iostream>
// naglowki SDL
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

	///Przeladowany konstruktor
	///@param channel kanal w jakim bedzie odtwarzany dzwiek
	///@param nickname pseudonim jakim ma byc przezywany dzwiek (ulatwia prace z dzwiekami)
	///@param filename sciezka do dzwieku ktory ma zostac zaladowany
	CSound(string nickname, string filename);

	/// Metoda otwierajaca plik dzwiekowy
	///@param channel kanal w jakim bedzie odtwarzany dzwiek
	///@param nickname pseudonim jakim ma byc przezywany dzwiek (ulatwia prace z dzwiekami)
	///@param filename sciezka do dzwieku ktory ma zostac zaladowany
	void openFile(string nickname, string filename);

	///Metoda zwracajaca id_ dzwieku
	///@return id_ dzwieku
	int GetId() const;



	///Metoda zwracajaca nickname_ dzwieku
	///@return nickname_ dzwieku
	string GetNickname() const;

	Mix_Chunk * GetSound() const;


private:

	///Licznik ulatwiajacy przypisywanie unikalnego id_ kazdemu dzwiekowi
	static int counter_;
	///wskaznik do Mix_Chunk przechowujacy informacje o dzwieku
	Mix_Chunk * sound;
	///Unikalny klucz muzyki
	int id_;
	///Nickname muzyki
	string nick_;

};

///Przeladowanie operatora<, potrzebny, aby w CAudioSystem mozna bylo uzywac std::set
bool operator<(const CSound& sound1, const CSound& sound2 );

#endif

//~~CSound.hpp