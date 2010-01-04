/** @file CVideoSystem.cpp
* @author Sebastian £uczak
* @date 2009.12.08
* @version 0.2_draft
* @brief Klasa jest odpowiedzialna za wyswietlanie w oparciu o OpenGL i operacje przeksztalcen sprite'ów
*	
*/

#include "CVideoSystem.hpp"
#include "utils.hpp"
#include "CTimer.hpp"

using namespace std;

///Konstruktor domyslny
CVideoSystem::CVideoSystem()
{
	cout << "Powstaje CVideoSystem" << endl;
}

///Destruktor
CVideoSystem::~CVideoSystem()
{
	cout << "CVideoSystem niszczony" << endl;
}

///Metoda wiazaca teksture sprite'a z OGL
/// @param sprite sprite do doczepienia
void CVideoSystem::bindTexture(const CSprite& sprite) const
{
		glBindTexture(GL_TEXTURE_2D, sprite.getTexID()); 
}

///Metoda wyswietlajaca sprite'a w zadanej lokalizacji
/// @param x wspolrzedna x (float)
/// @param y wspolrzedna y (float)
/// @param sprite sprite do wyswietlenia (CSprite)
void CVideoSystem::drawCSprite(const float x, const float y, const CSprite& sprite  ) const
{
	utils::TexDims tex_dims = sprite.getTexDimensions();
	//Dobierz barwe wyswietlania
	glColor4ub(255,255,255, sprite.getSpriteAlpha()); 
	//Wlacz mieszanie barw
	glEnable(GL_BLEND);
	//Wylacz test ZBufora
	glDisable(GL_DEPTH_TEST);
	//Ustaw funkcje mieszania barw z kanalem alpha (przezroczystosc)
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//doczep teksture
    bindTexture(sprite);
	//rysuj trojkatami (szybciej)
    glBegin(GL_TRIANGLE_STRIP); 
		glTexCoord2f(tex_dims.texMinX,tex_dims.texMinY);    glVertex2f(x,y);
		glTexCoord2f(tex_dims.texMaxX,tex_dims.texMinY);    glVertex2f(x+sprite.getSpriteWidth(),y);
        glTexCoord2f(tex_dims.texMinX,tex_dims.texMaxY);    glVertex2f(x,y+sprite.getSpriteHeight());
        glTexCoord2f(tex_dims.texMaxX,tex_dims.texMaxY);    glVertex2f(x+sprite.getSpriteWidth(),y+sprite.getSpriteHeight());
    glEnd();
	//przywroc maszyne stanow do ustawien poczatkowych
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
    glColor4ub(255,255,255,255);
}


void CVideoSystem::animateCAnimation(const float x, const float y, CAnimation& anim_set ) const
{
	// Rysuj klatke animacji
	drawCSprite(x, y, *(anim_set.animSet_[anim_set.currentFrame_].first));
	// Jesli jest juz czas na zmiane na nastepna klatke i animacja jest odtwarzana
	if( anim_set.animState_ && SDL_GetTicks() >= anim_set.nextFrameSwapTime_ )
    {
		// zmien klatke
		anim_set.currentFrame_ += anim_set.animMode_;
		cout << "CVideoSystem::animateCAnimation: Obecnie wyswietlana jest klatka: " << anim_set.currentFrame_ << endl;
        // sprawdz, czy animacja wyswietlila sie juz cala
		if( anim_set.currentFrame_ >= anim_set.numberOfFrames_ )
        {
			// jesli tak, to sprawdz, czy nalezy odtwarzac dalej
			switch(anim_set.animMode_)
            {
				case utils::ANIM_ONCE:
					anim_set.pauseCAnimation();
					anim_set.currentFrame_ = 0;
                    break;
				case utils::ANIM_LOOP:
					anim_set.currentFrame_ = 0;
                    break;
				case utils::ANIM_NONE:
                default:
					anim_set.resetCAnimation();
					cerr << "CVideoSystem::animateCAnimation: Nieznany tryb animacji!" << endl;
                    break;
            }
        }
		// oblicz czas do nastepnej zmiany klatki
		anim_set.setNextFrameSwapTime(SDL_GetTicks() + static_cast<Uint32>(anim_set.animSet_[anim_set.currentFrame_].second * 1000));
		cout << "CVideoSystem::animateCAnimation: Czas do nastepnej klatki: " << anim_set.nextFrameSwapTime_ << endl;
    }
}





//~~CVideoSystem.cpp
