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
	//konstruktor oparty o sciezke do pliku
	//np CSprite* sprite = new CSprite("../res/graphics/sprites/students/pl1.png");
	CSprite(string filename);

	///metoda otwierajaca plik i wywolujaca dolaczanie jego zawartosci do CSprite
	void openFile(string filename);
	///metoda dolaczajaca surface do CSprite ju¿ jako tekstura OGL
	void attachSprite(boost::shared_ptr<SDL_Surface> surface);
	///metoda ponownie ladujaca sprite'a w sytuacji, gdyby ogl sie wysypal
	void reloadSprite();
	///metoda resetujaca ustawienia tekstury OGL i powierzchni Sprite'a
	void releaseSprite();
	///metoda przypisujaca teksture do ogl
	void bindTexture() const;
	// zwracanie wartosci pol CSprite
	bool isLoaded() const;
	boost::shared_ptr<SDL_Surface> getSprite() const;
	float getSpriteWidth() const;
	float getSpriteHeight() const;
	int getSpriteAlpha() const;
	unsigned int getTexID() const;
	
	//metody do rysowania
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