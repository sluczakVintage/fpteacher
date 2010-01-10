/** @file CSound.cpp
* @author Rafal Malinowski
* @date 2009.12.18
* @version 0.1_draft
* @brief klasa CSound bedzie odpowiedzialna za przechowywanie informacji o dzwiekach
*	
*		
*/

#include "CSound.hpp"

using namespace std;

int CSound::licznik=0;

///Konstruktor Domyslny
CSound::CSound()
{
	cout << "CSound::CSound(): konstruktor domyslny" << endl;
}

///Destruktor Domyslny
CSound::~CSound()
{
	Mix_FreeChunk(sound);
	cout << "CSound::~CSound(): niszczenie CSound" << endl;
}

///Przeladowany konstruktor
///@param channel kanal w jakim bedzie odtwarzany dzwiek
///@param nickname pseudonim jakim ma byc przezywany dzwiek (ulatwia prace z dzwiekami)
///@param filename sciezka do dzwieku ktory ma zostac zaladowany
CSound::CSound(int channel, string nickname, string filename)
{
	sound = Mix_LoadWAV( filename.c_str() );
	cout << "Tworzymy nowy obiekt klasy CSound " << endl << endl;
	cout << "			" << Mix_GetError() << endl;
	id_=licznik;
	licznik++;
	nick_=nickname;
	channel_=channel;
	angle_=0;
	volume_=0;
	CAudioSystem::getInstance()-> addSound(*this);
}

///Metoda wlaczajaca odgrywanie dzwieku (wykorzystywana wylacznie przez CAudioSystem)
void CSound::Play()
{
	Mix_PlayChannel(channel_, sound, 0);
	SetPosition();
}

///Metoda wylaczajaca odgrywanie dzwieku (wykorzystywana wylacznie przez CAudioSystem)
void CSound::Stop()
{
		Mix_HaltChannel(channel_);
}


///Metoda ustawiajaca kierunek z ktorego bedzie slychac dzwiek, dzieki parametrowi angle_
void CSound::SetPosition()
{
	//Sint16 polozenie=GetAngle();
	Mix_SetPosition(channel_, angle_ , volume_);
}

///Metoda ustawiajaca kat pod jakim bedzie slychac dzwiek angle_
void CSound::SetAngle (Sint16 angle)
{
	angle_=angle;
	SetPosition();
}

///Metoda ustawiajaca glosnosc dzwieku
void CSound::SetVolume (int volume)
{
	volume_=volume;
	SetPosition();
}

///Metoda zwracajaca channel_ dzwieku
///@return channel_ dzwieku
int CSound::GetChannel() const
{
	return channel_;
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

///Metoda zwracajaca angle_ dzwieku
///@return angle_ dzwieku
Sint16 CSound::GetAngle() const
{
	return angle_;
}

///Metoda zwracajaca glosnosc dzwieku
///@return volume_ dzwieku
int CSound::GetVolume() const
{
	return volume_;
}

bool operator<(const CSound& sound1, const CSound& sound2 )
{
	int s1Id = sound1.GetId();
	int s2Id = sound2.GetId();
	if(s1Id<s2Id) return true;
	else return false;
}

//~~CSound.cpp