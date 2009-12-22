#include "CAudioSystem.hpp"
using namespace std;

CAudioSystem::CAudioSystem()
{
	//konstruktor domyslny
	int audio_rate = 22050;
	Uint16 audio_format = AUDIO_S16; /* 16-bit stereo */
	int audio_channels = 2;
	int audio_buffers = 512;


  if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers)) {
    cout <<"Unable to open audio!\n" << endl << endl;
	cout << Mix_GetError() << endl << endl;
	 }
}

CAudioSystem::~CAudioSystem()
{
	musics_.clear();
	//destruktor domyslny
}

void CAudioSystem::addMusic(const CMusic & music)
{
	//Jezeli muzyka juz istnieje
	//to kolejna nie zostanie dodana do CAudioSystem
	if(musics_.find(music) == musics_.end())
		{
		musics_.insert(music);
		cout << "	CAudioSystem::addMusics: dodano muzyke do CAudioSystem" << endl;
		}
	else 
		cout<<"		CAudioSystem::addMusics: muzyka juz istnieje \n";

	//if(musics_.find(music) == musics_.end()) 
	//{
	//	cout << "elo" << endl;
	//}

	//cout << "tralala" << endl;
}

void CAudioSystem::play_music(string nickname)
{
	cout << "wcisnieto play_music();" << endl;
	set<CMusic>::iterator it; 
  for ( it=musics_.begin() ; it != musics_.end(); it++ ) 
  {
	  if(it->GetNickname() == nickname) 
	  {
		  it->Play(); 
		  cout << "znaleziono muzyke" << endl;
	  }
  }
}

void CAudioSystem::pause_music(string nickname)
{
	cout << "wcisnieto pause_music();" << endl;
	set<CMusic>::iterator it; 
  for ( it=musics_.begin() ; it != musics_.end(); it++ ) 
  {
	  if(it->GetNickname() == nickname) 
	  {
		  it->Pause(); 
		  cout << "znaleziono muzyke" << endl;
	  }
  }
}
