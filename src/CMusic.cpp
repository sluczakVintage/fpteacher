/** @file CMusic.cpp
* @author Rafal Malinowski
* @date 2009.12.18
* @version 0.6
* @brief klasa CMusic bedzie odpowiedzialna za przechowywanie informacji o muzyce
*	
*		
*/
#include "CMusic.hpp"
using namespace logging;

// wyzerowanie licznika, ktory sluzy do dodawania muzykom kolejnych id
int CMusic::counter_=0;

///Konstruktor Domyslny
CMusic::CMusic()
{
	CLog::getInstance()->sss << "CMusic::CMusic(): konstruktor domyslny" << endl;
	logs(CLog::getInstance()->sss.str(), INFO);
}

///Destruktor
CMusic::~CMusic()
{
	//Mix_FreeMusic(music);
	CLog::getInstance()->sss << "CMusic::~CMusic(): niszczenie CMusic" << endl;
	logs(CLog::getInstance()->sss.str(), INFO);
}

///Przeladowany konstruktor
///@param nickname pseudonim jakim ma byc przezywana piosenka (ulatwia prace z muzyka)
///@param filename sciezka do muzyki ktora ma zostac zaladowana
CMusic::CMusic(string nickname, string filename)
{
	music = Mix_LoadMUS( filename.c_str() );
	CLog::getInstance()->sss << "Tworzymy nowy obiekt klasy CMusic " << endl << endl;
	logs(CLog::getInstance()->sss.str(), INFO);
	CLog::getInstance()->sss << Mix_GetError() << endl;
	logs(CLog::getInstance()->sss.str(), ERR);
	id_=counter_;
	counter_++;
	nick_=nickname;
	CAudioSystem::getInstance()-> addMusic(*this);
}

///Metoda wlaczajaca/wstrzumujaca odgrywanie muzyki (wykorzystywana wylacznie przez CAudioSystem)
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
		Mix_PlayMusic(music, -1);
	}
}

///Metoda wlaczajaca odgrywanie muzyki (wykorzystywana wylacznie przez CAudioSystem)
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
		Mix_PlayMusic(music, -1);
	}
}

///Metoda wstrzymujaca odgrywanie muzyki (wykorzystywana wylacznie przez CAudioSystem)
void CMusic::Pause()
{
	int playing = Mix_PlayingMusic();
	if(playing) 
	{
		Mix_PauseMusic();
	}
}

///Metoda wylaczajaca odgrywanie muzyki (wykorzystywana wylacznie przez CAudioSystem)
void CMusic::Stop()
{
	int playing = Mix_PlayingMusic();
	int paused = Mix_PausedMusic();
	if(playing || paused)
	{
		Mix_HaltMusic();
	}
}

///Metoda zwracajaca id_ muzyki
///@return id_ muzyki
int CMusic::GetId() const
{
	return id_;
}

///Metoda zwracajaca nickname_ muzyki
///@return nickname_ muzyki
string CMusic::GetNickname() const
{
	return nick_;
}

///Przeladowanie operatora<, potrzebny, aby w CAudioSystem mozna bylo uzywac std::set
bool operator<(const CMusic& music1, const CMusic& music2 )
{
	int m1Id = music1.GetId();
	int m2Id = music2.GetId();
	if(m1Id<m2Id) return true;
	else return false;
}


void CMusic::openFile(string nickname, string filename)
{
	music = Mix_LoadMUS( filename.c_str() );
	CLog::getInstance()->sss << "Tworzymy nowy obiekt klasy CMusic " << endl << endl;
	logs(CLog::getInstance()->sss.str(), INFO);
	CLog::getInstance()->sss << Mix_GetError() << endl;
	logs(CLog::getInstance()->sss.str(), ERR);
	id_=counter_;
	Mix_VolumeMusic(30);
	counter_++;
	nick_=nickname;
	CAudioSystem::getInstance()-> addMusic(*this);
}
//~~CMusic.cpp
