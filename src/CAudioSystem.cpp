/** @file CAudioSystem.cpp
* @author Rafal Malinowski
* @date 2009.12.18
* @version 0.6
* @brief klasa CAudioSystem bedzie odpowiedzialna za odtwarzanie wszystkich dzwiekow i muzyki
*	
*		
*/

#include "CAudioSystem.hpp"
using namespace std;

//Konstruktor Domyslny
CAudioSystem::CAudioSystem()
{
	int audio_rate = 22050;
	Uint16 audio_format = AUDIO_S16; /* 16-bit stereo */
	int audio_channels = 2;
	int audio_buffers = 512;

  if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers)) {
    cout <<"Unable to open audio!\n" << endl << endl;
	cout << Mix_GetError() << endl << endl;
	 }

  Mix_AllocateChannels(512);
}

//Destruktor
CAudioSystem::~CAudioSystem()
{
	musics_.clear();
	sounds_.clear();
}

// Metoda dodajaca muzyke do zbioru "musics_"
void CAudioSystem::addMusic(const CMusic & music)
{
	//Jezeli muzyka juz istnieje
	//to kolejna nie zostanie dodana do CAudioSystem
	 if ( musics_.insert( std::make_pair( music.GetNickname(), music ) ).second )
    {
		cout << "	CAudioSystem::addMusics: dodano muzyke do CAudioSystem" << endl;
		}
	else 
		cout<<"		CAudioSystem::addMusics: muzyka juz istnieje \n";
}

// Metoda dodajaca dzwiek do zbioru "sounds_"
void CAudioSystem::addSound(const CSound & sound)
{
    if ( sounds_.insert( std::make_pair( sound.GetNickname(), sound ) ).second )
    {
		cout << "CAudioSystem::addSound:CAudioSystem::addSounds: dodano dzwiek do CAudioSystem" << endl;
		}
	else 
		cout<<"CAudioSystem::addSound:CAudioSystem::addSounds: dzwiek juz istnieje \n";
}

// Metoda sluzaca do wlaczenia muzyki
void CAudioSystem::play_music(string nickname)
{
	cout << "CAudioSystem::play_music:wcisnieto play_music();" << endl;
	musics_.find(nickname)->second.Play();
	 cout << "CAudioSystem::play_music:znaleziono muzyke" << endl;
}

// Metoda sluzaca do wstrzymania muzyki
void CAudioSystem::pause_music(string nickname)
{
	cout << "CAudioSystem::pause_music:wcisnieto pause_music();" << endl;
	musics_.find(nickname)->second.Pause(); 
		  cout << "CAudioSystem::pause_music:znaleziono muzyke" << endl;
}

// Metoda sluzaca do zatrzymania muzyki
void CAudioSystem::stop_music(string nickname)
{
	cout << "CAudioSystem::stop_music:wcisnieto stop_music();" << endl;
	musics_.find(nickname)->second.Stop(); 
		  cout << "CAudioSystem::stop_music:znaleziono muzyke" << endl;
}

// Metoda sluzaca do wlaczenia dzwieku
int CAudioSystem::play_sound(string nickname, Sint16 location, int volume, int loops)
{
	//cout << "CAudioSystem::play_sound:wcisnieto play_sound();" << endl;
	int channel=-1;

	channel = Mix_PlayChannel(-1, sounds_.find(nickname)->second.GetSound(), loops);
	  Mix_SetPosition(channel, location , volume);
	  //(const_cast<CSound *>(&(*it)))->Play(); 
	  // cout << "CAudioSystem::play_sound:znaleziono dzwiek" << endl;
	  if(channel == -1)
		  cout << Mix_GetError() << endl << endl;

  //cout << "channel to " << channel << endl;
  return channel;
}

void CAudioSystem::stop_sound(int channel)
{
	Mix_HaltChannel(channel);
}

// Metoda sluzaca do ustawienia pozycji z ktorej ma byc odgrywany dzwiek (3D)
void CAudioSystem::set_sound_position(string nickname, Sint16 location, int volume)
{
	cout << "CAudioSystem::set_sound_position:wcisnieto zmiane polozenia dla dzwieku " << nickname << endl;

  //(const_cast<CSound *>(&(*it)))->SetAngle(location); 
  //(const_cast<CSound *>(&(*it)))->SetVolume(volume);
  cout << "CAudioSystem::set_sound_position:zmieniono polozenie dzwieku" << endl;
}

//~~CAudioSystem.cpp
