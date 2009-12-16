/**
* @author Sebastian £uczak
* @date 2009.12.08
* @version 0.2_draft
* @brief Klasa sprite'a przydzielonego do Entity
*	@todo Wydzielic loader plikow graficznych i zminimalizowac CSprite 
*	@todo Dodac konstruktor z CSprite
*/

#ifndef CSPRITE_H
#define CSPRITE_H

#include <string>
#include <cassert>

// naglowki boost
#include <boost/smart_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/ref.hpp>
// naglowki SDL
#include "SDL.h"	
#include "SDL_image.h"
#include "SDL_ttf.h"
//naglowki OpenGL
#include <windows.h>
#include <GL/gl.h>	
#include <GL/glu.h>	

#include "CVideoSystem.hpp"
#include "utils.hpp"


using namespace std;

class CVideoSystem;
class CSprite
{
public:
	///Konstruktor domyslny
	CSprite::CSprite() : sSprite(new SDL_Surface), sAlpha(255)
	{
	   releaseSprite();
	}
	///Destruktor
	CSprite::~CSprite()
	{
	   cout<<"Destruktor CSpirte" <<endl;
	   releaseSprite();
	}
	///konstruktor oparty o sciezke do pliku
	//np CSprite* sprite = new CSprite("../res/graphics/sprites/students/pl1.png");
	/// @param sciezka do ladowanego pliku
	CSprite(string filename);

	/// Metoda otwierajaca plik graficzny.
	/// Wywoluje metode przydzielajaca teksture i komplet parametrow CSprite
	/// @param sciezka do pliku graficznego
	void openFile(string filename);

	///metoda dolaczajaca surface do CSprite juz jako tekstura OGL
	void attachSprite(boost::shared_ptr<SDL_Surface> surface);

	///metoda ponownie ladujaca sprite'a w sytuacji, gdyby ogl sie wysypal
	void reloadSprite();

	///metoda resetujaca ustawienia tekstury OGL i powierzchni Sprite'a
	void releaseSprite();

	/// @return true jesli tekstura zaladowana do OGL
	bool CSprite::isLoaded() const;

	/// @return powierzchnia SDL CSprite
	boost::shared_ptr<SDL_Surface> CSprite::getSprite() const;

	/// @return szerokosc sprite'a (float)
	float CSprite::getSpriteWidth() const;

	/// @return wysokosc sprite'a (float)
	float CSprite::getSpriteHeight() const;

	/// @return alpha sprite'a (int)
	int CSprite::getSpriteAlpha() const;

	/// @return ID Textury OGL (unsigned int)
	unsigned int CSprite::getTexID() const;

	/// @return znormalizowane wymiary tekstury (utils::TexDims)
	utils::TexDims CSprite::getTexDimensions() const;
	
	/// Metoda przekazujaca rysowanie sprite'a do silnika
	/// @param x wartosc x typu int
	/// @param y wartosc y typu int
	void CSprite::drawCSprite(int x, int y) const;

	/// Metoda przekazujaca rysowanie sprite'a do silnika
	/// @param x wartosc x typu float
	/// @param y wartosc y typu float
	void CSprite::drawCSprite(float x, float y) const;

private:
	boost::shared_ptr<SDL_Surface> sSprite;  //SafeFreeSurface
 	
	unsigned int sTexID;
 	
	Uint8 sAlpha;
	GLfloat sWidth;
	GLfloat sHeight;

	utils::TexDims sTexDims;

};

#endif

//~~CSprite.hpp