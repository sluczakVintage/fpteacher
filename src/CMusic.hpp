/**
* @author Rafal Malinowski
* @date 2009.12.18
* @version 0.1_draft
* @brief klasa CMusic bedzie odpowiedzialna za przechowywanie informacji o muzyce
*	
*		
*/

#ifndef CMUSIC_H
#define CMUSIC_H

#include <string>
#include <cassert>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "SDL.h"
#include "SDL_mixer.h"
#include "CAudioSystem.hpp"


#include <boost/smart_ptr.hpp>

using namespace std;
class CMusic
{
public:
	CMusic();
	~CMusic();
	CMusic(string nickname, string filename);
	static int licznik;

	void Play_Pause();
	void Play();
	void Pause();
	void Stop();
	int GetId() const;
	string GetNickname() const ;
private:
	Mix_Music * music;
	int id_;
	string nick_;
};

bool operator<(const CMusic& music1, const CMusic& music2 );

#endif
