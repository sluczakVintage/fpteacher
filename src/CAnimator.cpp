/** @file CAnimator.cpp
* @author Sebastian £uczak
* @date 2010.01.08
* @version 0.1_draft
* @brief Klasa animatora, czyli minisystemu zarzadzajacego sekwencja animacji
* @more Dzialanie animatora w trybie ONCE - wyswietlany jest jednorazowo caly wektor animset'ow
							w trybie LOOP - sekwencja animset'ow jest powtarzana
							w trybie RANDOM - sekwencja animset'ow jest odtwarzana losowo, w trybie ciaglym
							w trybie NONE - animacja nie jest wykonywana
*/

#include "CAnimator.hpp"

using namespace utils;

CAnimator::CAnimator() : animState_(STOP), currentAnimSet_(0), currentFrame_(0), prioritySum_(0), lastFrameTime_(SDL_GetTicks()), animMode_(ANIM_LOOP)
{
	// Ziarno dla funkcji pseudolosowej
	srand( static_cast<int>( time(NULL) ) );
	cout << "CAnimator::CAnimator: Konstruktor CAnimator" << endl;
}

CAnimator::~CAnimator()
{
	// Wyczysc kontener z zestawami animacji
	clearCAnimator();
	cout << "CAnimator::~CAnimator: Destruktor CAnimator" << endl;
}

void CAnimator::refillCAnimator( const list< pair_si >  anim_names )
{
	// Wyczysc kontener z zestawami animacji
	clearCAnimator();
	// Dla kazdej pary wywolaj dodanie animacji (para uchwyt + priorytet)
	BOOST_FOREACH( pair_si p, anim_names )
	{
		addAnimation(p.first, p.second);
	}
	cout << "CAnimation::refillCAnimator: CAnimator zostal wypelniony" << endl;
}

void CAnimator::refillCAnimator( const list< pair_si >  anim_names, const utils::AnimMode& mode )
{
	animMode_ = mode;
	refillCAnimator(anim_names);
}

/// @TODO usunac te wersje metody
void CAnimator::refillCAnimator( const string anim_name, const int priority )
{
	clearCAnimator();
	addAnimation( anim_name, priority );
	cout << "CAnimation::refillCAnimator: CAnimator zostal wypelniony" << endl;
}

void CAnimator::addAnimation(const string filename, const int priority)
{
	// dodaj wartosc do sumy priorytetow
	prioritySum_ += priority;
	// dodaj uchwyt z priorytetem do wektora 
	animSetHandles_.push_back(make_pair(CAnimationMgr::getInstance()->getCAnimation(filename), priority) );
	cout << "CAnimator::addAnimation: Dodano animacje o nazwie " << filename << " i priorytecie " << priority << endl;
}

void CAnimator::clearCAnimator()
{
	// wyczysc wektor uchwytow i priorytetow
	animSetHandles_.erase(animSetHandles_.begin(), animSetHandles_.end());  ////Trzeba?
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
}

void CAnimator::playAnimation()
{
	// jesli animacja ma tryb ciagly
	if( animMode_ != ANIM_NONE ) {
		//jesli jest losowa
		if( animMode_ == ANIM_RANDOM )
		{				
			// wylosuj wartosc losowa
			int random_nr, curr_prior_sum = 0;
			random_nr = rand() % prioritySum_;
			// na bazie priorytetow wybierz odpowiedni zestaw animacji
			int i = 0;
			while( curr_prior_sum < random_nr && i <= static_cast<int>( animSetHandles_.size() ) )
			{
				curr_prior_sum += animSetHandles_[i].second;
				currentAnimSet_ = i;
				i++;
			}
		}
		animState_ = FORWARD;
		// ustaw czas ostatniej klatki
		lastFrameTime_ = SDL_GetTicks();
	}
	// w przeciwnym wypadku zatrzymaj animacje
	else
		animState_ = STOP;
}
// opakowanie dlugiego zapytania w krotszej formie
CAnimation* CAnimator::accessAnimation(const HCAnimation animation_handle) const
{
	return CAnimationMgr::getInstance()->getCAnimationInstance(animation_handle);
}

void CAnimator::animate(const float x, const float y)
{
	// Rysuj klatke animacji
	CVideoSystem::getInstance()->drawCSprite(x, y, CSpriteMgr::getInstance()->getCSpriteInstance(accessAnimation(animSetHandles_[currentAnimSet_].first)->getAnimSet()[currentFrame_].first));
	// Jesli jest juz czas na zmiane na nastepna klatke i animacja jest odtwarzana
	if( animState_ == FORWARD && ( accessAnimation(animSetHandles_[currentAnimSet_].first)->getDelayOf(currentFrame_) * 1000) < (SDL_GetTicks() - lastFrameTime_) )
    {
		// zmien klatke
		currentFrame_ += animState_;
		cout << "CAnimator::animate: Obecnie wyswietlana jest klatka: " << currentFrame_ << endl;
        // sprawdz, czy animacja wyswietlila sie juz cala
		if( currentFrame_ >= accessAnimation(animSetHandles_[currentAnimSet_].first)->getNoOfAnimationFrames() )
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
					cerr << "CAnimator::animate: Nieznany tryb animacji!" << endl;
                    break;
			}
			// zacznij od zerowej klatki
			currentFrame_ = 0;
        }
		// oblicz czas do nastepnej zmiany klatki
		lastFrameTime_ = SDL_GetTicks();
		cout << "CAnimator::animate: Czas do nastepnej klatki: " << lastFrameTime_ << endl;
    }
}

//~~CAnimator.cpp
