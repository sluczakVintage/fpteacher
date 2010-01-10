/**
* @author Sebastian Luczak
* @date 2009.12.08
* @version 0.2_draft
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
#include "utils.hpp"

using namespace std;

class COGLWindow : public CSingleton<COGLWindow>
{
	friend class CSingleton<COGLWindow>;

public:
	
	/// Metoda tworzaca okno gry zgodnie z podanymi paramterami
	/// @return true jesli tworzenie okna sie powiodlo
	bool createDisplay(int width = 1024, int height = 768, int bpp =  -1, std::string label = "default", bool fullscreen = false);
	
	/// Niszczy okno (opuszcza SDL)
	void closeDisplay();
	
	///Metoda ustawiajaca wstepnie parametry i maszyne stanow OpenGL
	void initOpenGL2D();
	
	/// Zmienia tryb okno/pelen ekran
	void toggleFullscreen();
	
	/// Zamienia bufory obrazu (aktualizuje wyswietlany obraz)
	void update();
	
	/// Czysci ekran wybranym kolorem
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

	bool sFullscreen_;
	bool sInitialized_;
	string sLabel_;
	SDL_Surface* sScreen_;
};
#endif

//~~COGLWindow.hpp
