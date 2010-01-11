/** \mainpage FPTeacher - dokumentacja projektu
 *
 * \section intro_sec Wstep
 *
 * FPTeacher jest gra komputerowa dla dwoch graczy polegajaca na prowadzeniu wykladu, badz przeszkadzaniu w wykladzie -
 * zaleznie od wyboru roli w grze.
 * \n
 * (dodac wycinki z dokumentacji)
 * \n
 * itd...
 * @file utils.hpp
 * @class utils::BadFileError utils.hpp
 * @class utils::BadBppError utils.hpp
 * @struct utils::TexDims utils.hpp
 * @brief plik w ktorym przechowywane sa rozne dodatkowe funkcje ulatwiajace i usprawniajace pisanie kodu
 **/

#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <cassert>
#include <sstream>
#include <stdexcept>

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

using namespace std;

/// @namespace utils Przechowuje funkcje i struktury uzywane w kodzie wielu klas

namespace utils
{
	/// FESTER
	const int FPS = 25;
	class BadFileError : public invalid_argument {
	public:
		///FESTER
		BadFileError(const string& msg = ""): invalid_argument(msg) {}
	};
	class BadBppError: public invalid_argument {
	public:
		///FESTER
		BadBppError(const string& msg = ""): invalid_argument(msg) {}
	};

	/// @enum AnimMode FESTER
	enum AnimMode
	{
			ANIM_ONCE,
			ANIM_LOOP,
			ANIM_NONE,
			ANIM_RANDOM
	};
	
	/// @enum AnimState FESTER
	enum AnimState
	{
	BACKWARD = -1,
	STOP = 0,
	FORWARD = 1,
	};

	/// @typedef Struktura przechowujaca wartosci graniczne tekstury OGL
	/// @struct TexDims
	 typedef struct{
		///FESTER
		GLfloat texMinX;
		///FESTER
		GLfloat texMinY;
		///FESTER
 		GLfloat texMaxX;
		///FESTER
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

	/// Operator strumieniowy dla enum'ow
	void operator>>(const std::istringstream& data, AnimMode& mode );

	/// @todo void SafeFreeFont(TTF_Font *&font); 

}

#endif 

//~~utils.hpp
