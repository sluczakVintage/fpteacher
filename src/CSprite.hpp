/**
* @author Sebastian £uczak
* @date 2009.12.08
* @version 0.2_draft
* @brief Klasa sprite'a przydzielonego do Entity
*	@todo Wydzielic loader plikow graficznych i zminimalizowac CSprite 
*	@todo //Dodac konstruktor z CSprite
*/

#ifndef CSPRITE_H
#define CSPRITE_H

#include <string>
#include <cassert>

// naglowki boost
#include <boost/smart_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/ref.hpp>
#include <boost/tuple/tuple.hpp>

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
	CSprite() : sSprite(new SDL_Surface), sAlpha(255), sName("empty")
	{
	   releaseSprite();
	}
	///Destruktor
	~CSprite()
	{
		cout<<"CSprite::~CSprite: Destruktor CSpirte" <<endl;
		releaseSprite();
	}
	///konstruktor oparty o sciezke do pliku
	//np CSprite* sprite = new CSprite("../res/graphics/sprites/students/pl1.png");
	/// @param sciezka do ladowanego pliku
//	CSprite(string filename);

	///konstruktor odpowiedzialny za animacje
	CSprite(const string filename, const int frame_number = 0, const int slice_w = 0);

	/// Metoda otwierajaca plik graficzny.
	/// Wywoluje metode przydzielajaca teksture i komplet parametrow CSprite
	/// @param sciezka do pliku graficznego
	bool openFile(const string filename, const int frame_number = 0, const int slice_w = 0);

	///metoda dolaczajaca surface do CSprite juz jako tekstura OGL
	void attachSprite(boost::shared_ptr<SDL_Surface> surface, const int frame_number = 0, const int slice_w = 0 );

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

	/// @return nazwa pliku zawierajacego CSprite (sprite)
	const string& CSprite::getSpriteName() const;
	
	/// @return znormalizowane wymiary tekstury (utils::TexDims)
	utils::TexDims CSprite::getTexDimensions() const;
	
private:
	boost::shared_ptr<SDL_Surface> sSprite;  //SafeFreeSurface
 	
	GLuint sTexID;
	string sName;  
	Uint8 sAlpha;
	GLfloat sWidth;
	GLfloat sHeight;
	boost::tuples::tuple<GLuint, Uint8, utils::TexDims> sHandle;

	utils::TexDims sTexDims;

};

#endif

//~~CSprite.hpp
