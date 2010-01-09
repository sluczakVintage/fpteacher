/** @file utils.cpp
* @author Sebastian £uczak
* @date 2009.12.08
* @version 0.2_draft
* @brief Plik zawierajacy funkcje stosowane w roznych klasach
*	
*/
#include <string>
#include <sstream>

#include "utils.hpp"
#include "../res/graphics/sprites/missing.xpm"

namespace utils
{
	//za SDL's testgl.c power_of_two
	/// @return przyblizenie danej wartosci wielokrotnoscia dwojki
	int PowerOfTwo(int num)
	{
		int value = 1;

		while(value < num) //wspÛ≥rzÍdne tekstury musza byc >= input
			value <<= 1;     //jak zadziala, zmienic na value *= 2
		return value;
	}
	
	/// Przerwarza powierzchnie SDL na teksture OpenGL
	/// @return Tekstura 2D OpenGL
	GLuint SurfaceToTexture(boost::shared_ptr<SDL_Surface> surface, utils::TexDims& texcoord)
	{
		GLuint texture;
		int w, h;
		
		SDL_Rect area;
		Uint32 saved_flags;
		Uint8  saved_alpha;
		GLenum texture_format;
		GLint no_of_colors;

		//aproksymacja szerokosci i wysokosci potÍgami dwÛjki
		w = utils::PowerOfTwo(surface->w);
		h = utils::PowerOfTwo(surface->h);
		// przydzielenie znormalizowanych wymiarow tekstury
		texcoord.texMinX = 0.0f; //min X
		texcoord.texMinY = 0.0f; //min Y
		texcoord.texMaxX = (GLfloat)surface->w / w;  //max X
		texcoord.texMaxY = (GLfloat)surface->h / h;  //max Y
		// tworzenie wskaznika na powierzchnie ktora zostanie odarta z flag SDL i znormalizowana do 
		// wyswietlania przez OGL
		boost::shared_ptr<SDL_Surface> temp (SDL_CreateRGBSurface(
			SDL_SWSURFACE,
			w, h,
			32,
	#if SDL_BYTEORDER == SDL_LIL_ENDIAN //endian specific color masks
			0x000000FF, 
			0x0000FF00, 
			0x00FF0000, 
			0xFF000000
	#else
			0xFF000000,
			0x00FF0000, 
			0x0000FF00, 
			0x000000FF
	#endif
		), boost::bind(&utils::SafeFreeSurface, _1) ) ;


		if(!temp.get())  
			throw std::runtime_error("utils::SurfaceToTexture(): Nie udalo sie stworzyc powierzchniRGBA temp");

		//zapisanie flag do zmiennych tymczasowych
		saved_flags = surface->flags&(SDL_SRCALPHA|SDL_RLEACCELOK);
		saved_alpha = surface->format->alpha;

		//usuniecie ustawien kanalu Alpha z powierzchni
		if((saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA)
			SDL_SetAlpha(surface.get(), 0, 0);

		//skopiowanie powierzchni odartej z flag i ustawien kanalu Alpha
		area.x = 0;
		area.y = 0;
		area.w = static_cast<Sint16>(surface->w);
		area.h = static_cast<Sint16>(surface->h);
		SDL_BlitSurface(surface.get(), &area, temp.get(), &area);


		//przywrocenie zapisanych flag
		if((saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA)
			SDL_SetAlpha(surface.get(), saved_flags, saved_alpha);

		//kontrola barw (Bpp)
		no_of_colors = temp->format->BytesPerPixel;
		try {
			if (no_of_colors == 4)
			{
				if (temp->format->Rmask == 0x000000FF)
					texture_format = GL_RGBA;
				else 
					throw BadFileError("Nieobslugiwany format pliku graficznego!");
			}
			else if (no_of_colors == 3)
			{
				if(temp->format->Rmask == 0x000000FF)
					texture_format = GL_RGB;
				else
					throw BadFileError("Nieobslugiwany format pliku graficznego!");
			}
			else
				throw BadFileError("Tekstura nie ma prawidlowego formatu" );
		}
		catch (BadFileError& x) {
			cout << "BadFileError: utils::SurfaceToTexture(): " << x.what() << "\nNie mozna wyswietlic!" << endl;
			throw;
		}

		//stworzenie tekstury OGL
		glGenTextures(1, &texture); 
		//ustawienie jej parametrow
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 
					0, 
					GL_RGBA, 
					w, h, 
					0, 
					texture_format, 
					GL_UNSIGNED_BYTE, 
					temp->pixels);

		return texture;
	}

	/// funkcja bezpiecznie ladujaca pliki obrazow
	/// @return sprytny wskaznik do powierzchni grafiki
	boost::shared_ptr<SDL_Surface> LoadImage(const std::string& filename)
	{
		try {
			boost::shared_ptr<SDL_Surface> image(
					IMG_Load(filename.c_str()),
					boost::bind(&utils::SafeFreeSurface, _1));
		
			if (!image.get())
				throw BadFileError(IMG_GetError());
		
			// dostosowanie powierzchni do wyswietlenia z kanalem alpha
			boost::shared_ptr<SDL_Surface> optimizedImage( 
					SDL_DisplayFormatAlpha(image.get()), 
					boost::bind(&utils::SafeFreeSurface, _1) ); 

			if (!optimizedImage.get())
				throw std::invalid_argument(IMG_GetError());

			cout<<"utils::LoadImage(): Obrazek "<< filename.c_str() << " zaladowano pomyslnie" <<endl;

			return optimizedImage;
		}
		catch (BadFileError& x) {
			cout << "BadFileError: utils::LoadImage(): " << x.what() << "\nLadowana grafika domyslna!" << endl;
			// Jesli nastapil wyjatek, zaladuj plik placeholder'owy z pamieci (format XPM) 
			// i dzialaj dalej
			boost::shared_ptr<SDL_Surface> image(
				IMG_ReadXPMFromArray(missing_xpm),
				boost::bind(&utils::SafeFreeSurface, _1));
			if(!image) 
			    throw std::invalid_argument(IMG_GetError());

			return image;
		}
	}

	/// Dealokator dla sprytnych wskaznikow na powierzchnie SDL
	void SafeFreeSurface(SDL_Surface* surface)
	{
		// boost::shared_ptr wywo≥uje podany przez uøytkownika destruktor
		// nawet, gdy przechowywany wskaünik nie jest prawid≥owy
		if (surface)
			std::cout<<"utils::SafeFreeSurface(): Dealokator SDL_Surface" <<std::endl;
			SDL_FreeSurface(surface);
	}

	void operator>>(const std::istringstream& data, AnimMode& mode )
	{
		if( data.str().find("ANIM_LOOP") ) mode = ANIM_LOOP;
	   else if(data.str().find("ANIM_ONCE") ) mode = ANIM_ONCE;
	   else mode = ANIM_NONE;
	}
}

//~~utils.cpp
