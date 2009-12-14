
#ifndef UTILS_H
#define UTILS_H

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
#include "utils.hpp"

using namespace std;

/// @namespace utils Przechowuje funkcje i struktury uzywane w kodzie wielu klas

namespace utils
{
template <unsigned n> double int_power(double x);
template <> double int_power<2>(double x);
template <> double int_power<1>(double x);
template <> double int_power<0>(double x);

/// @typedef Struktura przechowujaca wartosci graniczne tekstury OGL
 typedef struct{
    GLfloat texMinX;	
	GLfloat texMinY;
 	GLfloat texMaxX;
	GLfloat texMaxY;
    } TexDims;

/// @return przyblizenie danej wartosci wielokrotnoscia dwojki
int PowerOfTwo(int num);

/// Przerwarza powierzchnie SDL na teksture OpenGL
/// @return Tekstura 2D OpenGL
GLuint SurfaceToTexture(boost::shared_ptr<SDL_Surface> surface, utils::TexDims& texcoord);

/// funkcja bezpiecznie ladujaca pliki obrazow
/// @return sprytny wskaznik do powierzchni grafiki
boost::shared_ptr<SDL_Surface> LoadImage(const std::string& fileName);

/// Dealokator dla sprytnych wskaznikow na powierzchnie SDL
void SafeFreeSurface(SDL_Surface* surface);

/// @todo void SafeFreeFont(TTF_Font *&font); 

}

#endif 
