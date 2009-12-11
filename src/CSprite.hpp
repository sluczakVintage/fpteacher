/**
* @author Sebastian £uczak
* @date 2009.12.09
* @version 0.1_draft
* @brief 
*	
*	
*/
#ifndef CSPRITE_H
#define CSPRITE_H

#include <string>
#include <cassert>

// naglowki boost
#include <boost/smart_ptr.hpp>
#include <boost/bind.hpp>
// naglowki SDL
#include "SDL.h"	
#include "SDL_image.h"
#include "SDL_ttf.h"
//naglowki OpenGL
#include <windows.h>
#include <GL/gl.h>	
#include <GL/glu.h>	
#include "utils.hpp"

using namespace std;

class CSprite
{
public:
	///Konstruktor domyœlny
	CSprite();
	~CSprite();
	CSprite(string filename);

	void openFile(string filename);
	void attachSprite(boost::shared_ptr<SDL_Surface> surface);
	void reloadSprite();
	void releaseSprite();
	void bindTexture() const;

	bool isLoaded() const;
	boost::shared_ptr<SDL_Surface> getSprite() const;
	float getSpriteWidth() const;
	float getSpriteHeight() const;
	int getSpriteAlpha() const;
	unsigned int getTexID() const;
	

	void CSprite::tempDraw(float x, float y) const;
	void CSprite::tempDraw(int x, int y) const;
private:
	boost::shared_ptr<SDL_Surface> sSprite;  //SafeFreeSurface
 	
	unsigned int sTexID;
 	
	Uint8 sAlpha;

	GLfloat sWidth;
	GLfloat sHeight;

	GLfloat sTexMinX;	
	GLfloat sTexMinY;
 	
	GLfloat sTexMaxX;
	GLfloat sTexMaxY;

};

#endif