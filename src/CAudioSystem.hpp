/**\file
* @author Rafal Malinowski
* @date 2009.12.18
* @version 0.6
* @class CAudioSystem CAudioSystem.hpp
* @brief klasa CAudioSystem bedzie odpowiedzialna za odtwarzanie wszystkich dzwiekow i muzyki
*	
*		
*/

#ifndef CAUDIO_H
#define CAUDIO_H

#include <set>
#include <iostream>
#include <string>
#include "SDL.h"
#include "SDL_mixer.h"
#include "CSingleton.hpp"
#include "CMusic.hpp"
#include "CSound.hpp"


using namespace std;

class CMusic;
class CSound;

class CAudioSystem : public CSingleton<CAudioSystem>
{
	friend class CSingleton<CAudioSystem>;
public:
	///Konstruktor Domyslny
	CAudioSystem();
	///Destruktor
	~CAudioSystem();

	/// Metoda dodajaca muzyke do zbioru "musics_"
	/// @param music referencja do muzyki ktora ma zostac dodana do zbioru "musics_"
	void addMusic(const CMusic & music);

	/// Metoda dodajaca dzwiek do zbioru "sounds_"
	/// @param sound referencja do dzwieku ktory ma zostac dodany do zbioru "sounds_"
	void addSound(const CSound & sound);

	/// Metoda sluzaca do wlaczenia muzyki
	/// @param nickname nazwa muzyki jaka ma byc puszczona
	void play_music(string nickname);

	/// Metoda sluzaca do wstrzymania muzyki
	/// @param nickname nazwa muzyki jaka ma byc wstrzymana
	void pause_music(string nickname);

	/// Metoda sluzaca do zatrzymania muzyki
	/// @param nickname nazwa muzyki jaka ma byc zatrzymana
	void stop_music(string nickname);

	/// Metoda sluzaca do wlaczenia dzwieku
	/// @param nickname nazwa dzwieku jaki ma byc puszczony
	/// @param location kat z ktorego bedzie slychac dzwiek (0 - przed nami, 90 - z prawej, 180 - z tylu, 270 - z lewej)
	/// @param volume glosnosc dzwieku
	/// @param loops ilosc powtorzen ( 0 oznacza 1 powtorzenie, 1 oznacza 2 powtorzenia itd. Dodatkowo -1 oznacza granie w nieskonczonosc)
	/// @return numer kana³u na jakim odgrywany bedzie dzwiek
	int play_sound(string nickname, Sint16 location=0, int volume=128, int loops=0);

	/// Metoda sluzaca do zatrzymania dzwieku
	/// @param channel numer kanalu ktory ma zostac zatrzymany
	void stop_sound(int channel);

	/// Metoda sluzaca do ustawienia pozycji z ktorej ma byc odgrywany dzwiek (3D)
	/// @param nickname nazwa dzwieku ktorego pozycja ma byc ustalona
	/// @param location kat z ktorego bedzie slychac dzwiek (0 - przed nami, 90 - z prawej, 180 - z tylu, 270 - z lewej)
	/// @param volume dzwieku
	void set_sound_position(string nickname, Sint16 location, int volume);

private:

	/// Zbior przechowujacy wszystkie muzyki
	set<CMusic> musics_;

	/// Zbior przechowujacy wszystkie dzwieki
	set<CSound> sounds_;
};
#endif

//~~CAudioSystem.hpp