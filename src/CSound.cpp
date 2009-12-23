#include "CSound.hpp"

using namespace std;

int CSound::licznik=0;

CSound::CSound()
{
	cout << "CSound::CSound(): konstruktor domyslny" << endl;
}


CSound::~CSound()
{
	Mix_FreeChunk(sound);
	cout << "CSound::~CSound(): niszczenie CSound" << endl;
}

CSound::CSound(int channel, string nickname, string filename)
{
	//int audio_rate = 22050;
	//Uint16 audio_format = AUDIO_S16; /* 16-bit stereo */
	//int audio_channels = 2;
	//int audio_buffers = 512;
	sound = Mix_LoadWAV( filename.c_str() );
	cout << "Tworzymy nowy obiekt klasy CSound " << endl << endl;
	cout << "			" << Mix_GetError() << endl;
	id_=licznik;
	licznik++;
	nick_=nickname;
	channel_=channel;
	angle_=0;
	CAudioSystem::getInstance()-> addSound(*this);
}

void CSound::Play()
{
	Mix_PlayChannel(channel_, sound, 0);
	SetPosition();
}

void CSound::SetPosition()
{
	//Sint16 polozenie=GetAngle();
	Mix_SetPosition(channel_, angle_ , 128);
}
	
void CSound::SetAngle (Sint16 angle)
{
	angle_=angle;
	SetPosition();
}

Sint16 CSound::GetAngle() const
{
	return angle_;
}

int CSound::GetId() const
{
	return id_;
}

string CSound::GetNickname() const
{
	return nick_;
}


bool operator<(const CSound& sound1, const CSound& sound2 )
{
	int s1Id = sound1.GetId();
	int s2Id = sound2.GetId();
	if(s1Id<s2Id) return true;
	else return false;
}