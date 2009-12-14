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
	void COGLWindow::update()
	{
		SDL_GL_SwapBuffers();
	}
	
	/// Czysci ekran wybranym kolorem
	void clearDisplay(Uint8 red = 255, Uint8 green = 255, Uint8 blue = 255, Uint8 alpha = 255);

	/// Pobiera wskaznik do powierzchni SDL
	/// @return powierzchnia okna
	boost::shared_ptr<SDL_Surface> COGLWindow::getDisplayPtr()
	{
		boost::shared_ptr<SDL_Surface> s_screen_(sScreen_,
						boost::bind(&utils::SafeFreeSurface, _1)); 

		return s_screen_;
	}

	/// @return true jesli okno jest zainicjowane
	bool COGLWindow::isInitialized() const
	{
		return sInitialized_;
	}
	/// @return szerokosc okna
	int COGLWindow::getDisplayWidth() const
	{
		return sScreen_->w;
	}

	/// @return wysokosc okna
	int COGLWindow::getDisplayHeight() const
	{
		return sScreen_->h;
	}
	/// @return bbp okna
	int COGLWindow::getDisplayDepth() const
	{
		return sScreen_->format->BitsPerPixel;
	}
	/// @return true jesli tryb pelnoeranowy
	bool COGLWindow::isFullscreen() const
	{
		return sFullscreen_;
	}

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