/** @file CSound.cpp
* @author Rafal Malinowski
* @date 2009.12.18
* @version 0.6
* @brief klasa CSound bedzie odpowiedzialna za przechowywanie informacji o dzwiekach
*	
*		
*/

#include "CSound.hpp"

using namespace std;
using namespace logging;

int CSound::counter_=0;

///Konstruktor Domyslny
CSound::CSound()
{
	CLog::getInstance()->sss << "CSound::CSound(): konstruktor domyslny" << endl;
	logs(CLog::getInstance()->sss.str(), INFO);
}

///Destruktor
CSound::~CSound()
{
	//Mix_FreeChunk(sound);
	CLog::getInstance()->sss << "CSound::~CSound(): niszczenie CSound" << endl;
	logs(CLog::getInstance()->sss.str(), INFO);
}

///Przeladowany konstruktor
///@param channel kanal w jakim bedzie odtwarzany dzwiek
///@param nickname pseudonim jakim ma byc przezywany dzwiek (ulatwia prace z dzwiekami)
///@param filename sciezka do dzwieku ktory ma zostac zaladowany
CSound::CSound(string nickname, string filename)
{
	sound = Mix_LoadWAV( filename.c_str() );
	CLog::getInstance()->sss << "Tworzymy nowy obiekt klasy CSound " << endl << endl;
	logs(CLog::getInstance()->sss.str(), INFO);
	CLog::getInstance()->sss << Mix_GetError() << endl;
	logs(CLog::getInstance()->sss.str(), ERR);
	id_=counter_;
	counter_++;
	nick_=nickname;

	CAudioSystem::getInstance()-> addSound(*this);
}


///Metoda zwracajaca id_ dzwieku
///@return id_ dzwieku
int CSound::GetId() const
{
	return id_;
}

///Metoda zwracajaca nickname_ dzwieku
///@return nickname_ dzwieku
string CSound::GetNickname() const
{
	return nick_;
}

Mix_Chunk * CSound::GetSound() const
{
	return sound;
}


bool operator<(const CSound& sound1, const CSound& sound2 )
{
	int s1Id = sound1.GetId();
	int s2Id = sound2.GetId();
	if(s1Id<s2Id) return true;
	else return false;
}

void CSound::openFile(string nickname, string filename)
{
	sound = Mix_LoadWAV( filename.c_str() );
	CLog::getInstance()->sss << "Tworzymy nowy obiekt klasy CSound " << endl << endl;
	logs(CLog::getInstance()->sss.str(), INFO);
	CLog::getInstance()->sss << Mix_GetError() << endl;
	logs(CLog::getInstance()->sss.str(), ERR);
	id_=counter_;
	counter_++;
	nick_=nickname;
	CAudioSystem::getInstance()-> addSound(*this);
}
//~~CSound.cpp
