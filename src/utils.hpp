
#ifndef UTILS_H
#define UTILS_H

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

namespace utils
{
template <unsigned n> double int_power(double x);
template <> double int_power<2>(double x);
template <> double int_power<1>(double x);
template <> double int_power<0>(double x);

int PowerOfTwo(int num);
GLuint SurfaceToTexture(boost::shared_ptr<SDL_Surface> surface, GLfloat *texcoord);

void SafeFreeSurface(SDL_Surface* surface);

void SafeFreeFont(TTF_Font *&font); //TODO

}

#endif 
