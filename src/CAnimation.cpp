#include "CAnimation.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>

// naglowki boost
#include <boost/smart_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/ref.hpp>
using namespace utils;

CAnimation::CAnimation(const string filename) : currentFrame_(0), numberOfFrames_(0), nextFrameSwapTime_(0), animMode_(ANIM_ONCE)
{
	cout << "Konstruktor CAnimation z pliku" << endl;
	openFile(filename);
	playCAnimation(); /// @TODO TO MUSI BYC GDZIES INDZIEJ (chyba, ze zakladamy ciaglosc animacji)
}

bool CAnimation::openFile(const string filename)
{
	string s;
	string filename_prefix;
	size_t found;

	// pozyskanie prefiksu folderu z animacja
	found = filename.find_last_of("\\");
	filename_prefix = filename.substr(0,found);
	filename_prefix.append("\\");

	// kolejka 2 stronna zawierajaca odstepy miedzy klatkami
	queue<float> temp_delays;
	// szerokosc paska animacji
	int slice_w;
	{
		ifstream in(filename.c_str());
			/// TODO: obsluga wyjatkow
		if(!in) {
			cerr << "Nie mozna otworzyc "<< filename  << endl;  /// TODO prefiks
			return false;
		  }
		// proste pobieranie danych ze strumienia oparte na poszukiwaniu znacznikow
		while( getline(in, s) ) {

			istringstream data(s);
			string token;
			// pobierz ze strumienia pierwsza dane, ktora powinna byc token'em
			data >> token;
			cout << token << endl;
			if( token == "SPRITE") {
				string temp;
				//przytnij
				data.ignore(20, '='); 
				data >> temp;
				// dodaj prefiks do nazwy
				animSetName_ = filename_prefix;
				// i nazwe
				animSetName_.append(temp);
				cout << animSetName_ << endl; 
			}
			else if( token == "SLICE_W") {
				//przytnij
				data.ignore(20, '=');
				//pobierz szerokosc paska
				data >> slice_w;
				cout << slice_w << endl;
			}
			else if( token == "ANIMMODE") {
				//przytnij
				data.ignore(20, '='); 
				//pobierz tryb animacji (operator >> przeciazony)
				data >> animMode_;
				cout << animMode_ << endl; 
			}
			else if( token == "NUMOFFRAMES") {
				//przytnij
				data.ignore(20, '=');
				//pobierz liczbe klatek
				data >> skipws >> numberOfFrames_;
				cout << numberOfFrames_ << endl;
			}
			else if( token == "DELAYS") {
				//przytnij
				data.ignore(20, '=');
				//pobierz kolejne czasy klatek
				for(int i = 1; i <= numberOfFrames_; i++) {
					float delay;
					data >> skipws >> delay;
					temp_delays.push(delay);
					cout << delay << endl;
				}
			}
		}
	}
	// Ciecie plikow graficznych
	boost::shared_ptr<CSprite> temp_sprite;
	pair < boost::shared_ptr<CSprite>, float > anim_pair;
	//kolejno stworz CSprite'y skladowe animacji i przypisz odpowiadajace im czasy trwania klatek
	for( int i = 1; i <= numberOfFrames_; i++) {
		temp_sprite = boost::shared_ptr<CSprite>( new CSprite(animSetName_, i, slice_w) );
		anim_pair.first = temp_sprite;
		anim_pair.second = temp_delays.front();
		temp_delays.pop();
		animSet_.push_back(anim_pair);
	}
	return true;
}

void CAnimation::setAnimMode(const utils::AnimMode& mode )
{
	animMode_ = mode;
}

void CAnimation::setNextFrameSwapTime(const int time) 
{
	nextFrameSwapTime_ = time;
}

void CAnimation::resetCAnimation()
{
	animState_ = STOP;
	currentFrame_ = 0;
}

void CAnimation::pauseCAnimation()
{
	animState_ = STOP;
}

void CAnimation::playCAnimation()
{
	if( animMode_ != ANIM_NONE ) {
		animState_ = FORWARD;
		nextFrameSwapTime_= SDL_GetTicks() + static_cast<Uint32>(animSet_[0].second * 1000);
	}
	else
		animState_ = STOP;
}


//~~CAnimation.cpp
