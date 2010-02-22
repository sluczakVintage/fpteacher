/** @file CVideoSystem.cpp
* @author Sebastian luczak
* @date 2009.12.08
* @version 0.6_draft
* @brief Klasa jest odpowiedzialna za wyswietlanie w oparciu o OpenGL i operacje przeksztalcen sprite'ow
*	
*/

#include "CVideoSystem.hpp"
#include "utils.hpp"

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

void CVideoSystem::drawMouseCursor()
{
	GLfloat mousePositionX = static_cast<GLfloat>(CInput::getInstance()->getMouseX());
	GLfloat mousePositionY = static_cast<GLfloat>(CInput::getInstance()->getMouseY());
 	//Dobierz barwe wyswietlania
	glColor4ub(255,255,255, 255); 
	//Wlacz mieszanie barw
	glEnable(GL_BLEND);
	//Wylacz test ZBufora
	glDisable(GL_DEPTH_TEST);
	//Ustaw funkcje mieszania barw z kanalem alpha (przezroczystosc)
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//doczep teksture
	glBindTexture(GL_TEXTURE_2D, 7); 
	//rysuj trojkatami (szybciej)
    glBegin(GL_TRIANGLE_STRIP); 
		glTexCoord2f(0.f,0.f);    glVertex2f(mousePositionX,mousePositionY);
		glTexCoord2f(1.f,0.f);    glVertex2f(mousePositionX+92.f,mousePositionY);
        glTexCoord2f(0.f,1.f);    glVertex2f(mousePositionX,mousePositionY+128.f);
        glTexCoord2f(1.f,1.f);    glVertex2f(mousePositionX+92.f,mousePositionY+128.f);
    glEnd();
	//przywroc maszyne stanow do ustawien poczatkowych
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
    glColor4ub(255,255,255,255);

}


void CVideoSystem::drawCSprite(const float x,const float y, const CSprite* sprite ) const
{
	utils::TexDims tex_dims = sprite->getTexDimensions();
	//Dobierz barwe wyswietlania
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
		glTexCoord2f(tex_dims.texMaxX,tex_dims.texMinY);    glVertex2f(x+sprite->getSpriteWidth(),y);
        glTexCoord2f(tex_dims.texMinX,tex_dims.texMaxY);    glVertex2f(x,y+sprite->getSpriteHeight());
        glTexCoord2f(tex_dims.texMaxX,tex_dims.texMaxY);    glVertex2f(x+sprite->getSpriteWidth(),y+sprite->getSpriteHeight());
    glEnd();
	//przywroc maszyne stanow do ustawien poczatkowych
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
    glColor4ub(255,255,255,255);
}

/// Zamienia bufory obrazu (aktualizuje wyswietlany obraz)
void CVideoSystem::update()
{
	SDL_GL_SwapBuffers();
}

//~~CVideoSystem.cpp
