/**
* @author Rafal Malinowski
* @date 2009.12.18
* @version 0.1_draft
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
	friend CSingleton<CAudioSystem>;
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
	void play_sound(string nickname);

	/// Metoda sluzaca do ustawienia pozycji z ktorej ma byc odgrywany dzwiek (3D)
	/// @param nickname nazwa dzwieku ktorego pozycja ma byc ustalona
	/// @param polozenie kat z ktorego bedzie slychac dzwiek (0 - przed nami, 90 - z prawej, 180 - z tylu, 270 - z lewej)
	/// @param volume dzwieku
	void set_sound_position(string nickname, Sint16 polozenie, int volume);

private:

	/// Zbior przechowujacy wszystkie muzyki
	set<CMusic> musics_;

	/// Zbior przechowujacy wszystkie dzwieki
	set<CSound> sounds_;
};
#endif

//~~CAudioSystem.hpp