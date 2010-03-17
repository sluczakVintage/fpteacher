/** \mainpage FPTeacher - dokumentacja projektu
 *
 * \section intro_sec Wstep
 *
 * FPTEngine jest multiplatformowym silnikiem gry 2D opartym o biblioteki SimpleDirectMedia Library i OpenGL. 
 * \n
 * Przy implementacji stosowane byly biblioteki z rodziny Boost. 
 * \n
 * Do jego funkcjonalnosci nalezy akcelerowane sprzetowo wyswietlanie grafiki 2D w trybie okienkowym lub pelnoekranowym, pobieranie zdarzen z klawiatury i myszy, odtwarzanie dzwieku lokalizowanego w przestrzeni, pobieranie danych z plikow XML, zarzadzanie zasobami (grafiki, animacje, dzwieki), komunikacja sieciowa z drugim terminalem w dwuosobowym trybie gry, synchronizacja i integracja wszystkich wczesniej wymienionych podsystemow.
 *
 * @file utils.hpp
 * @author Sebastian Luczak
 * @date 2009.12.08
 * @version 0.6
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
#include <math.h>


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

#include "CLog.hpp"

//#include <GL/glext.h>

using namespace std;

/// @namespace utils Przechowuje funkcje i struktury uzywane w kodzie wielu klas

namespace utils
{
	/// sciezki do zasobow
	const string PATH_LOGS = "../doc/logs/";

	const string PATH_FONTS = "../res/graphics/fonts/";

	const string PATH_SOUNDS = "../res/sounds/";
	const string PATH_SOUNDS_ACTIONS = PATH_SOUNDS+"actions/";

	
	const string PATH_GUI = "../res/graphics/gui/";
	const string PATH_GUI_BUTTONS = PATH_GUI+"buttons/";

	const string PATH_CURSORS = "../res/graphics/cursors/";

	const string PATH_SPRITES = "../res/graphics/sprites/";
	const string PATH_SPRITES_AUDITORIUM_STUDENTS = PATH_SPRITES+"auditorium/students/";
	const string PATH_SPRITES_AUDITORIUM_TEACHER = PATH_SPRITES+"auditorium/teacher/";
	const string PATH_SPRITES_STUDENT_FRONT = PATH_SPRITES+"students/front/";
	const string PATH_SPRITES_STUDENT_REAR = PATH_SPRITES+"students/rear/";
	const string PATH_SPRITES_TEACHER = PATH_SPRITES+"teacher/";
	const string PATH_SPRITES_MINIGAMES = PATH_SPRITES+"minigames/";
	const string PATH_SPRITES_MINIGAMES_SLIDER = PATH_SPRITES_MINIGAMES+"slider/";

	const string PATH_ANIM_SEQUENCES = "../res/animsequences/";

	const string PATH_CONSTS = "../res/consts/CConsts.xml";

	/// Liczba klatek na sekunde (do ladowania z pliku)
	const int FPS = 30;

	enum 
	{
		THROW_TEACHER,
		THROW_STUDENTS
	};

	enum
	{
		OBJECT_CHALK,
		OBJECT_PAPERBALL/*,
		OBJECT_PLANE,
		OBJECT_CLOTH
		*/
	};
	struct Point
	{
		Point() : x_(0.f), y_(0.f), z_(0.f) {};
		Point(float x, float y, float z) : x_(x), y_(y), z_(z)	{};

		float x_;
		float y_;
		float z_;
	};

	struct Vector2f
	{
		Vector2f() : x_(0.f), y_(0.f){};
		Vector2f(float x, float y) : x_(x), y_(y) {};
		Vector2f(Point a, Point b) 
		{
			x_ = b.x_ - a.x_;
			y_ = b.y_ - a.y_;
		};

		float x_;
		float y_;
	};

	float distanceBetween(const Point a, const Point b);
	
	Vector2f multiplyVector2f(const Vector2f v, const float multiplier);

	Vector2f addVectors2f(const Vector2f v1, const Vector2f v2);

	Vector2f getOrthogonalVector2f(const Vector2f v);

	Point getEndPoint(const Point a, const Vector2f v);

	class BadFileError : public invalid_argument {
	public:
		///konstruktor domyslny klasy wyjatku blednego pliku
		BadFileError(const string& msg = ""): invalid_argument(msg) {}
	};
	class BadBppError: public invalid_argument {
	public:
		///konstruktor domyslny klasy wyjatku blednego BytesPerPixel
		BadBppError(const string& msg = ""): invalid_argument(msg) {}
	};

	/// @enum AnimMode Okresla tryb odtwarzania sekwencji zestawow animacji
	enum AnimMode
	{
			ANIM_ONCE,
			ANIM_LOOP,
			ANIM_NONE,
			ANIM_RANDOM
	};
	
	/// @enum AnimState Opisuje krok animacji, czyli, czy zestaw animuje sie do przodu, tylu (obecnie nieobslugiwane), czy jest zatrzymany (zapauzowany)
	enum AnimState
	{
	//BACKWARD = -1,
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

	/// @return przyblizenie danej wartosci wielokrotnoscia dwojki (dla funkcji OpenGL
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

	// @struct istring_less struktura operator porownania string'ow w indeksie nazw
    struct string_less
    {
		/// przeciazony operator wywolania funkcyjnego do porownywania zawartosci stringow w kontenerze map
		/// @param l string jako parametr z lewej strony operatora
		/// @param r string jako parametr z prawej strony operatora
		/// @return bool czy stringi l i r sa sobie rowne czy rozne
        bool operator () ( const std::string& l, const std::string& r ) const
            {  return ( l.compare(r) < 0 );  }
    };

	//void logs(int number);

	void randomizeRNG();
}

#endif 

//~~utils.hpp
