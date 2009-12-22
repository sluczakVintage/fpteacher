#include "CMusic.hpp"

int CMusic::licznik=0;

CMusic::CMusic()
{
	cout << "CMusic::CMusic(): konstruktor domyslny" << endl;
}

CMusic::~CMusic()
{
	Mix_FreeMusic(music);
	cout << "CMusic::~CMusic(): niszczenie CMusic" << endl;
}

CMusic::CMusic(string nickname, string filename)
{
	//int audio_rate = 22050;
	//Uint16 audio_format = AUDIO_S16; /* 16-bit stereo */
	//int audio_channels = 2;
	//int audio_buffers = 512;
	music = Mix_LoadMUS( filename.c_str() );
	cout << "Tworzymy nowy obiekt klasy CMusic " << endl << endl;
	cout << "			" << Mix_GetError() << endl;
	id_=licznik;
	licznik++;
	nick_=nickname;
	CAudioSystem::getInstance()-> addMusic(*this);
}

void CMusic::Play_Pause()
{
	int playing = Mix_PlayingMusic();
	int paused = Mix_PausedMusic();
	if (paused)
	{
		Mix_ResumeMusic();
	}
	else if (playing)
	{
		Mix_PauseMusic();
	}
	else
	{
		Mix_PlayMusic(music, 0);
	}
}

void CMusic::Play()
{
	int playing = Mix_PlayingMusic();
	int paused = Mix_PausedMusic();
	if (paused)
	{
		Mix_ResumeMusic();
	}
	else if(playing)
	{
		//do nothing
	}
	else 
	{
		Mix_PlayMusic(music, 0);
	}
}

void CMusic::Pause()
{
	int playing = Mix_PlayingMusic();
	if(playing) 
	{
		Mix_PauseMusic();
	}
}

void CMusic::Stop()
{
	int playing = Mix_PlayingMusic();
	int paused = Mix_PausedMusic();
	if(playing || paused)
	{
		Mix_HaltMusic();
	}
}

int CMusic::GetId() const
{
	return id_;
}

string CMusic::GetNickname() const
{
	return nick_;
}

bool operator<(const CMusic& music1, const CMusic& music2 )
{
	int m1Id = music1.GetId();
	int m2Id = music2.GetId();
	if(m1Id<m2Id) return true;
	else return false;
}