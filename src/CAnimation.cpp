/**\file
* @author Sebastian Luczak
* @date 2009.12.30
* @version 0.6
* @brief klasa CAnimation opakowuje animacje, odwolania do niej zwiazane sa z odtwarzaniem animacji
*	
*		
*/

#include "CAnimation.hpp"
using namespace logging;

CAnimation::~CAnimation() 
{
	releaseAnimation();
	CLog::getInstance()->sss << "CAnimation::~CAnimation: Destruktor CAnimation" << endl;
	logs(CLog::getInstance()->sss.str(), INFO);
}

// konstruktor domyslny
CAnimation::CAnimation() : numberOfFrames_(0)
{
	CLog::getInstance()->sss << "CAnimation::CAnimation: Konstruktor CAnimation" << endl;
	logs(CLog::getInstance()->sss.str(), INFO);
	
}

// konstruktor z pliku
CAnimation::CAnimation(const string filename) : numberOfFrames_(0)
{
	CLog::getInstance()->sss << "CAnimation::CAnimation: Konstruktor CAnimation z pliku" << endl;
	logs(CLog::getInstance()->sss.str(), INFO);
	openFile(filename);
}

// metoda otwierajaca plik i pobierajaca z niej animacje
bool CAnimation::openFile(const string filename)
{
	string s;
	string filename_prefix;
	size_t found;

	// pozyskanie prefiksu folderu z animacja
	found = filename.find_last_of(".");
	animSetName_ = filename.substr( 0, found );
	animSetName_.append(".png");
	//cout << animSetName_ << endl;

	// kolejka FIFO zawierajaca odstepy miedzy klatkami
	queue<float> temp_delays;
	// szerokosc paska animacji
	int slice_w;
	{
		ifstream in(filename.c_str());
		
		
		if(!in) 
		{
			loadDefault();
			return true;
		}
	

		// proste pobieranie danych ze strumienia oparte na poszukiwaniu znacznikow
		while( getline(in, s) ) {

			istringstream data(s);
			string token;
			// pobierz ze strumienia pierwsza dana, ktora powinna byc token'em
			data >> token;
			//cout << token << endl;
			if( token == "SLICE_W") {
				//przytnij
				data.ignore(20, '=');
				//pobierz szerokosc paska
				data >> slice_w;
				//cout << slice_w << endl;
			}
			else if( token == "NUMOFFRAMES") {
				//przytnij
				data.ignore(20, '=');
				//pobierz liczbe klatek
				data >> skipws >> numberOfFrames_;
				//cout << numberOfFrames_ << endl;
			}
			else if( token == "DELAYS") {
				//przytnij
				data.ignore(20, '=');
				//pobierz kolejne czasy klatek
				for(int i = 1; i <= numberOfFrames_; i++) {
					float delay;
					// i wstaw do kolejki z pominieciem bialych znakow
					data >> skipws >> delay;
					temp_delays.push(delay);
					//cout << delay << endl;
				}
			}
		}
	}
	// Ciecie plikow graficznych
	HCSprite temp_sprite_handle;
	//kolejno stworz CSprite'y skladowe animacji i przypisz odpowiadajace im czasy trwania klatek
	for( int i = 1; i <= numberOfFrames_; i++) {
		temp_sprite_handle = CSpriteMgr::getInstance()->getCSprite(animSetName_, i, slice_w);
		animSet_.push_back(std::make_pair(temp_sprite_handle, temp_delays.front()));
		temp_delays.pop();
	}
	if(numberOfFrames_ == static_cast<int>(animSet_.size() ) ) 
	{	
		CLog::getInstance()->sss << "CAnimation::openFile: Ladowanie animacji sie powiodlo." << endl;
		logs(CLog::getInstance()->sss.str(), INFO);
		return true;
	}
	else
	{
		CLog::getInstance()->sss << "CAnimation::openFile: Ladowanie animacji sie nie powiodlo!" << endl;
		logs(CLog::getInstance()->sss.str(), ERR);
		return false;
	}
}

void CAnimation::loadDefault()
{
	numberOfFrames_ = 1;
	animSet_.push_back(std::make_pair(CSpriteMgr::getInstance()->getCSprite("default"), 0.f));

}

// zwolnij wektor z uchwytami do klatek animacji i odstepami
void CAnimation::releaseAnimation()
{
	animSet_.erase(animSet_.begin(), animSet_.end());
	animSet_.clear();
	CLog::getInstance()->sss << "CAnimation::releaseAnimation: Wektor uchwytow zniszczony" << endl;
	logs(CLog::getInstance()->sss.str(), INFO);
}

// pobierz opoznienie dla danej ramki
float CAnimation::getDelayOf(int frame) const
{
	return animSet_[frame].second;
}

// pobierz liczbe klatek animacji
int CAnimation::getNoOfAnimationFrames() const
{
	return numberOfFrames_;
}

// pobierz nazwe animacji
const string& CAnimation::getAnimationName() const
{
	return animSetName_;
}

// pobierz pare sprite + jego opoznienie
const vector< pair< HCSprite, float > >& CAnimation::getAnimSet() const
{
	return animSet_;
}

//~~CAnimation.cpp
