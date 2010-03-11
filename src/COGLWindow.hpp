/**\file
* @author Sebastian Luczak
* @date 2009.12.08
* @version 0.6
* @class COGLWindow COGLWindow.hpp
* @brief Klasa jest odpowiedzialna za inicjalizacje podsystemow SDL i OpenGL i utworzenie okna w 
*	wybranym trybie
*	
*/

#ifndef	COGLWINDOW_H
#define COGLWINDOW_H


#include <iostream>
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
//naglowki klas aplikacji
#include "CSingleton.hpp"
#include "CSpriteMgr.hpp"
#include "CFontMgr.hpp"
#include "utils.hpp"

#include "CLog.hpp"

using namespace std;

class COGLWindow : public CSingleton<COGLWindow>
{
	friend class CSingleton<COGLWindow>;

public:
	
	/// Metoda tworzaca okno gry zgodnie z podanymi paramterami
	/// @return true jesli tworzenie okna sie powiodlo
	bool createDisplay(int width = 1024, int height = 768, int bpp =  -1, std::string label = "FPTeacher v0.4", bool fullscreen = false);
	
	/// Niszczy okno (opuszcza SDL)
	void closeDisplay();
	
	///Metoda ustawiajaca wstepnie parametry i maszyne stanow OpenGL
	void initOpenGL2D();
	
	/// Zmienia tryb okno/pelen ekran
	void toggleFullscreen();
		
	/// Czysci ekran wybranym kolorem
	/// @param red wartosc czerwonej skladowej
	/// @param green wartosc zielonej skladowej
	/// @param blue wartosc niebieskiej skladowej
	/// @param alpha wartosc skladowej alpha
	void clearDisplay(Uint8 red = 255, Uint8 green = 255, Uint8 blue = 255, Uint8 alpha = 255);

	/// Pobiera wskaznik do powierzchni SDL
	/// @return powierzchnia okna
	boost::shared_ptr<SDL_Surface> getDisplayPtr();

	/// @return true jesli okno jest zainicjowane
	bool isInitialized() const;

	/// @return szerokosc okna
	int getDisplayWidth() const;

	/// @return wysokosc okna
	int getDisplayHeight() const;

	/// @return bbp okna
	int getDisplayDepth() const;

	/// @return true jesli tryb pelnoeranowy
	bool isFullscreen() const;

private:
	///Konstruktor domyslny
	COGLWindow();
	///Destruktor
	~COGLWindow();
	/// Wartosc okreslajaca czy ustawiony jest tryb pelnoekranowy
	bool sFullscreen_;
	/// Wartosc okreslajaca czy okno jest zainicjowane
	bool sInitialized_;
	/// Etykieta okna
	string sLabel_;
	/// powierzchnia ekranu
	SDL_Surface* sScreen_;

};
#endif

//~~COGLWindow.hpp
