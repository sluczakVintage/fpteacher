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

CAnimation::CAnimation(const string filename) : currentFrame_(0), numberOfFrames_(0), timeToNextFrame_(0), animMode_(ANIM_ONCE)
{
	cout << "Konstruktor CAnimation z pliku" << endl;
	openFile(filename);
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

	queue<int> temp_delays;
	int slice_w;
	{
		ifstream in(filename.c_str());
			/// TODO: obsluga bledow
		if(!in) {
			cerr << "Nie mozna otworzyc "<< filename  << endl;  /// TODO prefiks
			return false;
		  }
			// proste pobieranie danych ze strumienia;
		while( getline(in, s) ) {

			istringstream data(s);
			string token;

			data >> token;
			cout << token << endl;
			if( token == "SPRITE") {
				string temp;

				data.ignore(20, '='); 
				data >> temp;

				animSetName_ = filename_prefix;
				animSetName_.append(temp);
				cout << animSetName_ << endl; 
			}
			else if( token == "SLICE_W") {
				data.ignore(20, '=');
				data >> slice_w;
				cout << slice_w << endl;
			}
			else if( token == "ANIMMODE") {
				data.ignore(20, '='); 
				data >> animMode_;
				cout << animMode_ << endl; 
			}
			else if( token == "NUMOFFRAMES") {
				data.ignore(20, '=');
				data >> skipws >> numberOfFrames_;
				cout << numberOfFrames_ << endl;
			}
			else if( token == "DELAYS") {
				data.ignore(20, '=');
				for(int i = 1; i <= numberOfFrames_; i++) {
					int d;
					data >> skipws >> d;
					temp_delays.push(d);
					cout << d << endl;
				}
			}
		}
	}
	// Ciecie plikow
	boost::shared_ptr<CSprite> temp_sprite;
	pair < boost::shared_ptr<CSprite>, int > anim_pair;

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

void CAnimation::setTimeToNextFrame(const int time) 
{
	timeToNextFrame_ = time;
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
		timeToNextFrame_= SDL_GetTicks() + animSet_[0].second;
	}
	else
		animState_ = STOP;
}


//~~CAnimation.cpp
