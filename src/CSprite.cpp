/** @file CSprite.cpp
* @author Sebastian �uczak
* @date 2009.12.08
* @version 0.2_draft
* @brief Klasa sprite'a przydzielonego do Entity
* @todo Wydzielic loader plikow graficznych i zminimalizowac CSprite 
*/

#include "CSprite.hpp"

///Konstruktor z pliku o podanej sciezce
CSprite::CSprite(const string filename, const int frame_number, const int slice_w) : 
		sSprite(new SDL_Surface), 
		sAlpha(255),
		sName("empty")
{
	cout << "CSprite::CSprite: Konstruktor CSprite z pliku" << endl;
	openFile(filename, frame_number, slice_w);
}
/// Metoda otwierajaca plik graficzny.
/// Wywoluje metode przydzielajaca teksture i komplet parametrow CSprite
/// @param filename sciezka do pliku graficznego
/// @return czy otwarcie pliku sie powiodlo
bool CSprite::openFile(const string filename, const int frame_number, const int slice_w)
{
	sName = filename;
	boost::shared_ptr<SDL_Surface> image = utils::LoadImage( filename.c_str() );
	attachSprite(image, frame_number, slice_w);

	return true;
}
/// Metoda przydzielajaca CSprite teksture i parametry na bazie powierzchni odczytanej z pliku
/// @param surface sprytny wskaznik na powierzchnie SDL
void CSprite::attachSprite(boost::shared_ptr<SDL_Surface> surface, const int frame_number, const int slice_w)
{
	utils::TexDims tex_dims;
	//na wszelki wypadek wyzeruj wszelkie parametry tekstury i sprite'a
	releaseSprite();		
	try{
	if (!surface.get())
		throw utils::BadFileError("CSprite::attachSprite(): Bledny parametr surface!");
	}
	catch (utils::BadFileError& x) {
		cerr << "BadFileError: " << x.what() << endl;
		throw;
	}

	// obsluga animacji
	/// @TODO Jak starczy czasu, trzeba dac temu wiecej finezji!!
	if(frame_number != 0)
	{
		SDL_Rect src_clip_rect, dst_clip_rect;
		src_clip_rect.x = static_cast<Sint16>( ( frame_number - 1 ) * slice_w);
		src_clip_rect.w = static_cast<Sint16>(slice_w);
		src_clip_rect.y = 0;
		src_clip_rect.h = static_cast<Sint16>(surface->h);

		dst_clip_rect.x = 0;
		dst_clip_rect.y = 0;

		boost::shared_ptr<SDL_Surface> clipped_image (SDL_CreateRGBSurface(
			SDL_SWSURFACE,
			src_clip_rect.w, src_clip_rect.h,
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

		if(!clipped_image.get())  
			throw std::runtime_error("CSprite::attachSprite(): Nie udalo sie stworzyc powierzchniRGBA clipped_image");

		Uint32 saved_flags;
		Uint8  saved_alpha;
		//zapisanie flag do zmiennych tymczasowych
		saved_flags = surface->flags&(SDL_SRCALPHA|SDL_RLEACCELOK);
		saved_alpha = surface->format->alpha;

		//usuniecie ustawien kanalu Alpha z powierzchni
		if((saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA)
			SDL_SetAlpha(surface.get(), 0, 0);
		//obciecie powierzchni do zadanych wymiarow
		SDL_BlitSurface(surface.get(), &src_clip_rect, clipped_image.get(), &dst_clip_rect);
		surface = clipped_image;
		//przywrocenie zapisanych flag
		if((saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA)
			SDL_SetAlpha(surface.get(), saved_flags, saved_alpha);

		cout << "CSprite::attachSprite(): klatka nr " << frame_number << " jest przycieta " << slice_w << endl;
	}


	//przypisz wartosci do pol CSprite
	sWidth = static_cast<float>(surface->w);
	sHeight = static_cast<float>(surface->h);
	
	//przetworz SDL_Surface na teksture OGL
	sTexID = utils::SurfaceToTexture(surface, tex_dims);
	//nadaj wymiary teksturze na podstawie wartosci z funckji SurfaceToTexture
	sTexDims = tex_dims;
	//ostatecznie przypisz sama powierzchnie do pola sSprite
	sSprite = surface;

	sHandle = boost::tuples::make_tuple(sTexID , sAlpha, sTexDims);
}

///przeladowuje powierzchnie SDL
void CSprite::reloadSprite()
{
    //na wypadek potrzeby przeladowania sprite'a w oknie OGL
	boost::shared_ptr<SDL_Surface> toReload( 
						new SDL_Surface,
						boost::bind(&utils::SafeFreeSurface, _1)); 
	toReload = sSprite;	

    attachSprite(toReload);
}

/// Metoda zerujaca ustawienia sprite'a
void CSprite::releaseSprite()
{
	//przywr�� stan Sprite'a
	if(glIsTexture(sTexID))
		glDeleteTextures(1,&sTexID);
	sTexDims.texMaxX = sTexDims.texMaxY = sTexDims.texMinX = sTexDims.texMinY = 0.f;
	sTexID = 0;
	sWidth = sHeight = 0;
}
/// @return true jesli tekstura zaladowana do OGL
bool CSprite::isLoaded() const
{
	return glIsTexture(sTexID) == GL_TRUE;
}

/// @return powierzchnia SDL CSprite
boost::shared_ptr<SDL_Surface> CSprite::getSprite() const
{
	return sSprite;
}

/// @return nazwa pliku zawierajacego CSprite (sprite)
const string& CSprite::getSpriteName() const
{
	return sName;
}

/// @return szerokosc sprite'a (float)
float CSprite::getSpriteWidth() const
{
	return static_cast<float>(sWidth);
}

/// @return wysokosc sprite'a (float)
float CSprite::getSpriteHeight() const
{
	return static_cast<float>(sHeight);
}

/// @return alpha sprite'a (int)
int CSprite::getSpriteAlpha() const
{
	return static_cast<int>(sAlpha);
}

/// @return ID Textury OGL (unsigned int)
unsigned int CSprite::getTexID() const
{
	return sTexID;
}

/// @return znormalizowane wymiary tekstury (utils::TexDims)
utils::TexDims CSprite::getTexDimensions() const
{ 
	return sTexDims;
}

//~~CSprite.cpp
