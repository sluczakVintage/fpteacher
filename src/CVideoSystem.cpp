/** @file CVideoSystem.cpp
* @author Sebastian luczak
* @date 2009.12.08
* @version 0.6_draft
* @brief Klasa jest odpowiedzialna za wyswietlanie w oparciu o OpenGL i operacje przeksztalcen sprite'ow
*	
*/

#include "CVideoSystem.hpp"


using namespace std;
using namespace logging;

///Konstruktor domyslny
CVideoSystem::CVideoSystem() : scaleRatio_(1.0f), userDefinedAlpha_(-1)
{
	cursor_ = new CAnimator;
	CLog::getInstance()->sss << "Powstaje CVideoSystem" << endl;
	logs(CLog::getInstance()->sss.str(), INFO);
}

///Destruktor
CVideoSystem::~CVideoSystem()
{
	delete cursor_;
	CLog::getInstance()->sss << "CVideoSystem niszczony" << endl;
	logs(CLog::getInstance()->sss.str(), INFO);
}

///Metoda wiazaca teksture sprite'a z OGL
/// @param sprite sprite do doczepienia
void CVideoSystem::bindTexture(const CSprite& sprite) const
{
		glBindTexture(GL_TEXTURE_2D, sprite.getTexID()); 
}

void CVideoSystem::loadCursor(const string& filename, float offset_x, float offset_y)
{
	cursorOffsetX_ = offset_x;
	cursorOffsetY_ = offset_y;
	cursor_->openFile(utils::PATH_CURSORS+filename, 2);
	cursor_->playAnimation();
}

void CVideoSystem::drawMouseCursor() const
{
	GLfloat mousePositionX = (static_cast<GLfloat>(CInput::getInstance()->getMouseX()) - cursorOffsetX_);
	GLfloat mousePositionY = (static_cast<GLfloat>(CInput::getInstance()->getMouseY()) - cursorOffsetY_);
 	
	cursor_->animate(mousePositionX, mousePositionY);
}


void CVideoSystem::drawCSprite(const float x,const float y, const CSprite* sprite )
{
	utils::TexDims tex_dims = sprite->getTexDimensions();
	//Dobierz barwe wyswietlania
	if(userDefinedAlpha_ != -1)
	{
		if(userDefinedAlpha_ >= 0 && userDefinedAlpha_ <= 255)
			glColor4ub(255,255,255, userDefinedAlpha_); 
		else
			glColor4ub(255,255,255, sprite->getSpriteAlpha()); 
	}
	else
		glColor4ub(255,255,255, sprite->getSpriteAlpha()); 
		
	//Wlacz mieszanie barw
	glEnable(GL_BLEND);
	//Wylacz test ZBufora
	glDisable(GL_DEPTH_TEST);
	//Ustaw funkcje mieszania barw z kanalem alpha (przezroczystosc)
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//doczep teksture
	glBindTexture(GL_TEXTURE_2D, sprite->getTexID()); 
	//rysuj trojkatami (szybciej)
    glBegin(GL_TRIANGLE_STRIP); 
		glTexCoord2f(tex_dims.texMinX,tex_dims.texMinY);    glVertex2f(x,y);
		glTexCoord2f(tex_dims.texMaxX,tex_dims.texMinY);    glVertex2f(x+sprite->getSpriteWidth()*scaleRatio_ ,y);
        glTexCoord2f(tex_dims.texMinX,tex_dims.texMaxY);    glVertex2f(x,y+sprite->getSpriteHeight()*scaleRatio_ );
        glTexCoord2f(tex_dims.texMaxX,tex_dims.texMaxY);    glVertex2f(x+sprite->getSpriteWidth()*scaleRatio_ ,y+sprite->getSpriteHeight()*scaleRatio_ );
    glEnd();
	//przywroc maszyne stanow do ustawien poczatkowych
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
    glColor4ub(255,255,255,255);

	if(userDefinedAlpha_ != -1)
		userDefinedAlpha_ = -1;

	if(scaleRatio_ != 1.0f)
		scaleRatio_ = 1.0f;
}

/// Zamienia bufory obrazu (aktualizuje wyswietlany obraz)
void CVideoSystem::setScale(const float scale_ratio)
{
	scaleRatio_ = scale_ratio;
}

// Ustawia wartosc alpha oczekiwana przez uzytkownika
void CVideoSystem::setAlpha(const int alpha)
{
	userDefinedAlpha_ = alpha;
}


/// Zamienia bufory obrazu (aktualizuje wyswietlany obraz)
void CVideoSystem::update()
{
	SDL_GL_SwapBuffers();
}

//~~CVideoSystem.cpp
