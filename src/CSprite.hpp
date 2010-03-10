/**\file
* @author Sebastian Luczak
* @date 2009.12.08
* @version 0.6
* @class CSprite CSprite.hpp
* @brief Klasa sprite'a o szerokim zastosowaniu
*	@todo Wydzielic loader plikow graficznych i zminimalizowac CSprite 
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
#if defined(_WIN32) 
#include <windows.h> 
#endif
#include <GL/gl.h>	
#include <GL/glu.h>	
//naglowki aplikacji
#include "utils.hpp"

#include "CLog.hpp"

using namespace std;

class CSprite
{
public:
	///Konstruktor domyslny
	CSprite();
	///Destruktor
	~CSprite();
	
	///konstruktor oparty o sciezke do pliku
	//np CSprite* sprite = new CSprite("../res/graphics/sprites/students/pl1.png");
	/// @param filename sciezka do ladowanego pliku
	/// @param frame_number dotyczy zestawow animacji - liczba klatek na jaka ma byc pociety dany sprite
	/// @param slice_w dotyczy zestawow animacji - szerokosc klatki
	CSprite(const string filename, const int frame_number = 0, const int slice_w = 0);

	/// Metoda otwierajaca plik graficzny.
	/// Wywoluje metode przydzielajaca teksture i komplet parametrow CSprite
	/// @param filename sciezka do pliku graficznego
	/// @param frame_number dotyczy zestawow animacji - liczba klatek na jaka ma byc pociety dany sprite
	/// @param slice_w dotyczy zestawow animacji - szerokosc klatki
	/// @return wartosc logiczna okreslajaca powodzenie otwarcia pliku
	bool openFile(const string filename, const int frame_number = 0, const int slice_w = 0);

	///metoda dolaczajaca surface do CSprite juz jako tekstura OGL
	/// @param surface sprytny wskaznik na powierzchnie SDL
	/// @param frame_number dotyczy zestawow animacji - liczba klatek na jaka ma byc pociety dany sprite
	/// @param slice_w dotyczy zestawow animacji - szerokosc klatki
	void attachSprite(boost::shared_ptr<SDL_Surface> surface, const int frame_number = 0, const int slice_w = 0 );

	///metoda ponownie ladujaca sprite'a w sytuacji, gdyby ogl sie wysypal
	void reloadSprite();

	///metoda resetujaca ustawienia tekstury OpenGL i powierzchni Sprite'a
	void releaseSprite();

	/// @return true jesli tekstura zaladowana do OpenGL
	bool isLoaded() const;

	/// @return powierzchnia SDL CSprite
	boost::shared_ptr<SDL_Surface> getSprite() const;

	/// @return szerokosc sprite'a (float)
	float getSpriteWidth() const;

	/// @return wysokosc sprite'a (float)
	float getSpriteHeight() const;

	/// @return alpha sprite'a (int)
	int getSpriteAlpha() const;

	/// @return ID Textury OGL (unsigned int)
	unsigned int getTexID() const;

	/// @return nazwa pliku zawierajacego CSprite (sprite)
	const string& getSpriteName() const;
	
	/// @return znormalizowane wymiary tekstury (utils::TexDims)
	utils::TexDims getTexDimensions() const;
	
private:
	/// sprytny wskaznik na powierzchnie sprite'a
	boost::shared_ptr<SDL_Surface> sSprite_;  
	/// identyfikator tekstury OGL
	GLuint sTexID_;
	/// nazwa sprite'a
	string sName_;  
	/// wartosc alpha
	Uint8 sAlpha_;
	/// szerokosc sprite'a
	GLfloat sWidth_;
	/// wysokosc sprite'a
	GLfloat sHeight_;
	/// wymiary tekstury OGL
	utils::TexDims sTexDims_;

};

#endif

//~~CSprite.hpp
