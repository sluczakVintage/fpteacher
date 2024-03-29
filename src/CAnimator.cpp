/** @file CAnimator.cpp
* @author Sebastian luczak
* @date 2010.01.08
* @version 0.6
* @brief Klasa animatora, czyli minisystemu zarzadzajacego sekwencja animacji
*  Dzialanie animatora w trybie ONCE - wyswietlany jest jednorazowo caly wektor animset'ow
							w trybie LOOP - sekwencja animset'ow jest powtarzana
							w trybie RANDOM - sekwencja animset'ow jest odtwarzana losowo, w trybie ciaglym
							w trybie NONE - animacja nie jest wykonywana
*/

#include "CAnimator.hpp"
using namespace logging;

using namespace utils;

CAnimator::CAnimator() : animState_(STOP), currentAnimSet_(0), currentFrame_(0), prioritySum_(0), lastFrameTime_(SDL_GetTicks()), animMode_(ANIM_LOOP), soundChannel_(0)
{
	CLog::getInstance()->sss << "CAnimator::CAnimator: Konstruktor CAnimator"  << endl;
	logs(CLog::getInstance()->sss.str(), INFO);
}

CAnimator::~CAnimator()
{
	// Wyczysc kontener z zestawami animacji
	clearCAnimator();
	CLog::getInstance()->sss << "CAnimator::~CAnimator: Destruktor CAnimator"  << endl;
	logs(CLog::getInstance()->sss.str(), INFO);
}

//
// metoda otwierajaca plik i pobierajaca z niej animacje
bool CAnimator::openFile(const string filename, int type)
{
	// lista zawierajaca nazwy zestawow animacji
	list< tuple_sai > anim_sets;
	string s;
	string anim_filename_prefix;

	if(CLogic::getInstance()->getIsTeacher())
		anim_filename_prefix = PATH_SPRITES_STUDENT_FRONT;
	else
		anim_filename_prefix = PATH_SPRITES_STUDENT_REAR;

	if(type == 1)
		anim_filename_prefix = PATH_SPRITES_MINIGAMES;
	if(type == 2)
		anim_filename_prefix = PATH_CURSORS;
	  
	{
		ifstream in(filename.c_str());
		
		
		if(!in) {
			refillCAnimatorDefault();
			setAnimMode(ANIM_NONE);
			CLog::getInstance()->sss << "CAnimator::openFile: Bledna sekwencja animacji. Zaladowano obrazek domyslny!"  << endl;
			logs(CLog::getInstance()->sss.str(), WARNING);
			return true;
		}
		

		// proste pobieranie danych ze strumienia oparte na poszukiwaniu znacznikow
		while( getline(in, s) ) {

			istringstream data(s);
			string token;
			// pobierz ze strumienia pierwsza dana, ktora powinna byc token'em
			data >> token; 
			//cout << token << endl;
			if( token == "ANIMMODE") {
				data.ignore(20, '='); 
				data >> animMode_;
				//cout << animMode_ << endl; 
			}
			else if( token == "ANIMSET") {

				string anim_name, sound_name, temp;
				int priority = 0;

				data.ignore(20, '='); 
				data >> temp;

				anim_name = anim_filename_prefix;
				// i nazwe animacji
				anim_name.append(temp);
				
				data >> temp;

				sound_name = PATH_SOUNDS_ACTIONS;
				// i nazwe dzwieku
				if(temp != "NULL")
					sound_name.append(temp);
				else
					sound_name = "NULL";
				data >> skipws >> priority;

				anim_sets.push_back(boost::make_tuple(anim_name, sound_name, priority));
				//cout << anim_name << endl;
				//cout << sound_name << endl;
				//cout << priority << endl;
			}
		}
	}
	refillCAnimator(anim_sets);
	return true;
}


void CAnimator::refillCAnimator( const list< tuple_sai >  anim_names )
{
	// Wyczysc kontener z zestawami animacji
	clearCAnimator();
	// Dla kazdej pary wywolaj dodanie animacji (para uchwyt + priorytet)
	BOOST_FOREACH( tuple_sai t, anim_names )
	{
		addAnimation(t.get<0>(), t.get<1>(), t.get<2>());
	}
	CLog::getInstance()->sss << "CAnimation::refillCAnimator: CAnimator zostal wypelniony"  << endl;
	logs(CLog::getInstance()->sss.str(), INFO);
}

void CAnimator::refillCAnimator( const list< tuple_sai >  anim_names, const utils::AnimMode& mode )
{
	animMode_ = mode;
	refillCAnimator(anim_names);
}

// uzywane przy default
void CAnimator::refillCAnimatorDefault()
{
	clearCAnimator();
	addAnimation( "default", "NULL", 1);
	CLog::getInstance()->sss << "CAnimation::refillCAnimator: CAnimator zostal wypelniony" << endl;
	logs(CLog::getInstance()->sss.str(), INFO);
}

void CAnimator::addAnimation(const string filename, const string audioname, const int priority)
{
	CSound sound;
	if( audioname != "NULL" )
		sound.openFile(audioname, audioname);
	// dodaj wartosc do sumy priorytetow
	prioritySum_ += priority;
	// dodaj uchwyt z priorytetem do wektora 
	animSetHandles_.push_back(boost::make_tuple(CAnimationMgr::getInstance()->getCAnimation(filename), audioname, priority) );
	CLog::getInstance()->sss << "CAnimator::addAnimation: Dodano animacje o nazwie " << filename << " dzwieku " << audioname << " i priorytecie " << priority << endl;
	logs(CLog::getInstance()->sss.str(), INFO);
}

void CAnimator::clearCAnimator()
{
	// wyczysc wektor uchwytow i priorytetow
	animSetHandles_.erase(animSetHandles_.begin(), animSetHandles_.end()); 
	animSetHandles_.clear();
}

void CAnimator::setAnimMode(const utils::AnimMode& mode )
{
	animMode_ = mode;
}


void CAnimator::resetCAnimator()
{
	animState_ = STOP;
	currentFrame_ = 0;
}

void CAnimator::pauseAnimation()
{
	animState_ = STOP;
	if(soundChannel_ != -1)
		CAudioSystem::getInstance()->stop_sound(soundChannel_);
}

void CAnimator::playAnimation()
{
	int i = 0;
	// jesli animacja ma tryb ciagly
	if( animMode_ != ANIM_NONE ) {
		//jesli jest losowa
		if( animMode_ == ANIM_RANDOM )
		{				
			int random_nr, curr_prior_sum = 0;

			static boost::mt19937 rng(static_cast<unsigned int>(std::time(0)));

			boost::uniform_int<> distrib(0,prioritySum_);      
                                      
			boost::variate_generator<boost::mt19937&, boost::uniform_int<> > probability(rng, distrib);                       

			random_nr = probability();

			// na bazie priorytetow wybierz odpowiedni zestaw animacji
			while( curr_prior_sum < random_nr && i <= static_cast<int>( animSetHandles_.size() ) )
			{
				curr_prior_sum += animSetHandles_[i].get<2>();
				currentAnimSet_ = i;
				i++;
			}
		}
		animState_ = FORWARD;
		if( animSetHandles_[currentAnimSet_].get<1>() != "NULL")
			soundChannel_ = CAudioSystem::getInstance()->play_sound(animSetHandles_[currentAnimSet_].get<1>(), location_, volume_);
		else 
			soundChannel_ = -1;
		// ustaw czas ostatniej klatki
		lastFrameTime_ = SDL_GetTicks();
	}
	// w przeciwnym wypadku zatrzymaj animacje
	else
	{
		animState_ = STOP;
		if( soundChannel_ != -1)
			CAudioSystem::getInstance()->stop_sound(soundChannel_);
	}	
}
// opakowanie dlugiego zapytania w krotszej formie
CAnimation* CAnimator::accessAnimation(const HCAnimation animation_handle) const
{
	return CAnimationMgr::getInstance()->getCAnimationPtr(animation_handle);
}

void CAnimator::setAudioParam(const int position, const int distance) 
{
	location_ = position;
	volume_ = distance;
}

void CAnimator::animate(const float x, const float y)
{
	// Rysuj klatke animacji
	CVideoSystem::getInstance()->drawCSprite(x, y, CSpriteMgr::getInstance()->getCSpritePtr(accessAnimation(animSetHandles_[currentAnimSet_].get<0>())->getAnimSet()[currentFrame_].first));
	// Jesli jest juz czas na zmiane na nastepna klatke i animacja jest odtwarzana
	if( animState_ == FORWARD && ( accessAnimation(animSetHandles_[currentAnimSet_].get<0>())->getDelayOf(currentFrame_) * 1000) < (SDL_GetTicks() - lastFrameTime_) )
    {
		// zmien klatke
		currentFrame_ += animState_;
		//cout << "CAnimator::animate: Obecnie wyswietlana jest klatka: " << currentFrame_ << endl;
        // sprawdz, czy animacja wyswietlila sie juz cala
		if( currentFrame_ >= accessAnimation(animSetHandles_[currentAnimSet_].get<0>())->getNoOfAnimationFrames() )
        {
			// jesli tak, to sprawdz, czy nalezy odtwarzac dalej
			switch(animMode_)
            {
				// jesli sekwencja ma byc odtworzona tylko jednokrotnie
				case utils::ANIM_ONCE:
					// sprawdz, czy numer obecnie odtwarzanej podsekwencji jest maksymalnym (co oznacza, ze sekwencja zostala odegrana w calosci)
					if( currentAnimSet_ + 1 >= static_cast<int>( animSetHandles_.size() ) )
					{
						// jesli tak, to zakoncz odtwarzanie
						currentAnimSet_ = 0;
						pauseAnimation();
					}
					else
					{
						currentAnimSet_++;
						playAnimation();
					}
				
					break;
				
				// jesli sekwencja ma byc zapetlana
				case utils::ANIM_LOOP:
					// gdy zostanie osiagniety koniec sekwencji
					if( currentAnimSet_ + 1 >= static_cast<int>( animSetHandles_.size() ) )
						// zacznij od poczatku
						currentAnimSet_ = 0;
					else
						// w innym wypadku przejdz do nastepnej sekwencji
						currentAnimSet_++;
					playAnimation();
                    
					break;
				// jesli sekwencja ma byc odtwarzana w sposob losowy
				case utils::ANIM_RANDOM:
					// przejdz do metody w ktorej jest losowana nastepna podsekwencja
					playAnimation();

					break;
				
				// jesli sekwencja jest statyczna (nie jest animacja)
				case utils::ANIM_NONE:
				default:
					// wstrzymaj ja
					pauseAnimation();
					CLog::getInstance()->sss << "CAnimator::animate: Nieznany tryb animacji!" << endl;
					logs(CLog::getInstance()->sss.str(), ERR);
					
                    break;
			}
			// zacznij od zerowej klatki
			currentFrame_ = 0;
        }
		// oblicz czas do nastepnej zmiany klatki
		lastFrameTime_ = SDL_GetTicks();
	//	cout << "CAnimator::animate: Czas obecnej klatki: " << lastFrameTime_ << endl;
    }
}

//~~CAnimator.cpp
