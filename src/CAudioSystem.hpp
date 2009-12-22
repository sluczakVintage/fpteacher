/**
* @author Rafal Malinowski
* @date 2009.12.18
* @version 0.1_draft
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
	CAudioSystem();
	~CAudioSystem();

	void play_music(string nickname);
	void pause_music(string nickname);
	void stop_music(string nickname);

	void play_sound(string nickname);
	void set_sound_position(string nickname, Sint16 polozenie);

	void addMusic(const CMusic & music);
	void addSound(const CSound & sound);
private:
	set<CMusic> musics_;
	set<CSound> sounds_;
};
#endif
