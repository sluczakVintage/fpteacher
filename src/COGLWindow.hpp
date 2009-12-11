/**
* @author Sebastian £uczak
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
#include <windows.h>
#include <GL/gl.h>	
#include <GL/glu.h>	
//naglowki klas aplikacji
#include "CSingleton.hpp"
#include "utils.hpp"

using namespace std;

class COGLWindow : public CSingleton<COGLWindow>
{
	friend CSingleton<COGLWindow>;

public:
	/// Tworzy okno z podana etykieta
	bool createDisplay(int width = 640, int height = 480, int bpp =  -1, std::string label = "default", bool fullscreen = false);
	/// Niszczy okno (opuszcza SDL)
	void closeDisplay();
	/// Zmienia tryb okno/pelen ekran
	void toggleFullscreen();
	/// Zamienia bufory obrazu (aktualizuje wyswietlany obraz
	void update();
	void clearDisplay(Uint8 red = 0, Uint8 green = 0, Uint8 blue = 0, Uint8 alpha = 255);
	void initOpenGL2D();

	/// Zwraca wskaznik na powierzchnie wyswietlana
	/// Zmienic na smartptr
	SDL_Surface* getDisplayPtr();
	/// Zwraca, czy okno zostalo stworzone
	bool isInitialized() const;
	/// Zwraca szerokosc
	int getDisplayWidth() const;
	/// Zwraca wysokosc
	int getDisplayHeight() const;
	/// Zwraca bpp
	int getDisplayDepth() const;
	/// Zwraca, czy tryb jest pelnoekranowy
	bool isFullscreen() const;

private:
	COGLWindow();
	~COGLWindow();


	bool sFullscreen_;
	bool sInitialized_;
	string sLabel_;
	SDL_Surface* sScreen_;
};
#endif