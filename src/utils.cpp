#include "utils.hpp"

namespace utils
{
	template <unsigned n> double int_power(double x) {
		return int_power<2>( int_power<n/2>(x) ) * int_power<n%2>(x);
	}
	template <> double int_power<2>(double x) {
		return x*x;
	}
	template <> double int_power<1>(double x) {
		return x;
	}
	template <> double int_power<0>(double x) {
		return 1.0;
	}

	//za SDL's testgl.c power_of_two
	int PowerOfTwo(int num)
	{
		int value = 1;

		while(value < num) //wspÛ≥rzÍdne tekstury musza byc >= input
			value <<= 1;     //jak zadziala, zmienic na value *= 2
		return value;
	}
	
	GLuint SurfaceToTexture(boost::shared_ptr<SDL_Surface> surface, GLfloat *texcoord)
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
		texcoord[0] = 0.0f; //min X
		texcoord[1] = 0.0f; //min Y
		texcoord[2] = (GLfloat)surface->w / w;  //max X
		texcoord[3] = (GLfloat)surface->h / h;  //max Y

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

		if(!temp.get())  //log??
			return 0;

		//alpha
		saved_flags = surface->flags&(SDL_SRCALPHA|SDL_RLEACCELOK);
		saved_alpha = surface->format->alpha;

		if((saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA)
			SDL_SetAlpha(surface.get(), 0, 0);

		//copy surface (do not alter passed surface to allow this function to be used in special situations)
		area.x = 0;
		area.y = 0;
		area.w = static_cast<Sint16>(surface->w);
		area.h = static_cast<Sint16>(surface->h);
		SDL_BlitSurface(surface.get(), &area, temp.get(), &area);

		//przywrocenie zapisanej wartosci alpha
		if((saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA)
			SDL_SetAlpha(surface.get(), saved_flags, saved_alpha);

		
		no_of_colors = temp->format->BytesPerPixel;
		if (no_of_colors == 4)
		{
			if (temp->format->Rmask == 0x000000FF)
				texture_format = GL_RGBA;
			else
				std::cout << "Nieobs≥ugiwany format pliku graficznego!" << std::endl;
				std::cerr << "Nieobs≥ugiwany format pliku graficznego!" << std::endl;
		}
		else if (no_of_colors == 3)
		{
			if(temp->format->Rmask == 0x000000FF)
				texture_format = GL_RGB;
			else
				std::cout << "Nieobs≥ugiwany format pliku graficznego!" << std::endl;
				std::cerr << "Nieobs≥ugiwany format pliku graficznego!" << std::endl;
		}
		else
		{
			std::cerr << "Tekstura nie ma prawidlowego formatu" << std::endl;
			//try catch
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

	boost::shared_ptr<SDL_Surface> LoadImage(const std::string& fileName)
	{

		boost::shared_ptr<SDL_Surface> image(
				IMG_Load(fileName.c_str()),
				boost::bind(&utils::SafeFreeSurface, _1));
		cout <<IMG_Load(fileName.c_str()) << endl;
		cout << image << endl;
		if (!image.get())
			throw std::runtime_error(IMG_GetError());
		boost::shared_ptr<SDL_Surface> optimizedImage( 
				SDL_DisplayFormatAlpha(image.get()), 
				boost::bind(&utils::SafeFreeSurface, _1) ); 
		 if (!optimizedImage.get())
			throw std::runtime_error(IMG_GetError());
		return optimizedImage;

	}


	void SafeFreeSurface(SDL_Surface* surface)
	{
		// boost::shared_ptr wywo≥uje podany przez uøytkownika destruktor
		// nawet, gdy przechowywany wskaünik nie jest prawid≥owy
		if (surface)
			SDL_FreeSurface(surface);
	}

}