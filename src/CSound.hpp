/**
* @author Rafal Malinowski
* @date 2009.12.18
* @version 0.1_draft
* @brief klasa CSound bedzie odpowiedzialna za przechowywanie informacji o dzwiekach
*	
*		
*/

#ifndef CSOUND_H
#define CSOUND_H

#include <string>
#include <cassert>
//#include <stdio.h>
//#include <stdlib.h>
#include <iostream>
#include "SDL.h"
#include "SDL_mixer.h"
#include "CAudioSystem.hpp"


//#include <boost/smart_ptr.hpp>

using namespace std;
class CSound
{
public:
	CSound();
	~CSound();
	CSound(int channel, string nickname, string filename);
	static int licznik;

	int GetId() const;
	int GetChannel() const;
	string GetNickname() const;
	Sint16 GetAngle() const;

	void Play();
	void SetPosition();
	void SetAngle (Sint16 angle);
private:

	Sint16 angle_;
	Mix_Chunk * sound;
	int id_;
	int channel_;
	string nick_;

};

bool operator<(const CSound& sound1, const CSound& sound2 );

#endif
