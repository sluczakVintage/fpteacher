#include "CSprite.hpp"

CSprite::CSprite() : 
	sSprite(new SDL_Surface),
	sAlpha(255)
{

   // Release();
}


CSprite::CSprite(std::string filename) : 
    sSprite(new SDL_Surface),
    sAlpha(255)
{
    openFile(filename);
}

CSprite::~CSprite()
{
    releaseSprite();
}


void CSprite::openFile(std::string filename)
{
	boost::shared_ptr<SDL_Surface> image(
						IMG_Load( filename.c_str() ),
						boost::bind(&utils::SafeFreeSurface, _1)) ;
	assert(image.get()); //zmienic na log lub try catch
	boost::shared_ptr<SDL_Surface> optimizedImage( 
						SDL_DisplayFormat( image.get() ),
						boost::bind(&utils::SafeFreeSurface, _1));
    attachSprite(optimizedImage);
}

void CSprite::attachSprite(boost::shared_ptr<SDL_Surface> surface)
{
    GLfloat coord[4];

	//na wszelki wypadek wyzeruj wszelkie parametry tekstury i sprite'a
	releaseSprite();		
    
	assert(surface.get());
	//tymczasowy wskaznik do wykonania operacji
	boost::shared_ptr<SDL_Surface> temp(
						SDL_DisplayFormatAlpha(surface.get()), 
						boost::bind(&utils::SafeFreeSurface, _1) ); 
    assert(temp.get());
	//jesli sie udalo, to przypisz tymczasowa wartosc
	surface = temp;    
	//przypisz wartosci do pol CSprite
	sWidth = static_cast<float>(surface->w);
	sHeight = static_cast<float>(surface->h);
	//przetworz SDL_Surface na teksture OGL
	sTexID = utils::SurfaceToTexture(surface,coord);
	sTexMinX = coord[0];
	sTexMinY = coord[1];
	sTexMaxX = coord[2];
	sTexMaxY = coord[3];
	//ostatecznie przypisz sama powierzchnie do pola sSprite
	sSprite = surface;
}


void CSprite::reloadSprite()
{
    //na wypadek potrzeby przeladowania sprite'a w oknie OGL
	boost::shared_ptr<SDL_Surface> toReload( 
						new SDL_Surface,
						boost::bind(&utils::SafeFreeSurface, _1)); 
	toReload = sSprite;
	utils::SafeFreeSurface(sSprite.get());  

    attachSprite(toReload);
}

void CSprite::releaseSprite()
{
    //set everything back the way it came
    if(glIsTexture(sTexID))
        glDeleteTextures(1,&sTexID);
    sTexMinX = sTexMinY = sTexMaxX = sTexMaxY = 0.0f;
    sTexID = 0;
    sWidth = sHeight = 0;
	utils::SafeFreeSurface(sSprite.get());
}

void CSprite::tempDraw(int x, int y) const
{
    tempDraw(static_cast<float>(x),static_cast<float>(y));
}

void CSprite::tempDraw(float x, float y) const
{
    glColor4ub(255,255,255,sAlpha); 
    bindTexture();
    glBegin(GL_TRIANGLE_STRIP); 
        glTexCoord2f(sTexMinX,sTexMinY);    glVertex2f(x,y);
        glTexCoord2f(sTexMaxX,sTexMinY);    glVertex2f(x+sWidth,y);
        glTexCoord2f(sTexMinX,sTexMaxY);    glVertex2f(x,y+sHeight);
        glTexCoord2f(sTexMaxX,sTexMaxY);    glVertex2f(x+sWidth,y+sHeight);
    glEnd();
    glColor4ub(255,255,255,255);
}


void CSprite::bindTexture() const
{
      glBindTexture(GL_TEXTURE_2D, sTexID); //log, ?
}

bool CSprite::isLoaded() const
{
    return glIsTexture(sTexID) == GL_TRUE;
}

boost::shared_ptr<SDL_Surface> CSprite::getSprite() const
{
    return sSprite;
}


float CSprite::getSpriteWidth() const
{
    return static_cast<float>(sWidth);
}

float CSprite::getSpriteHeight() const
{
    return static_cast<float>(sHeight);
}

int CSprite::getSpriteAlpha() const
{
    return static_cast<int>(sAlpha);
}

unsigned int CSprite::getTexID() const
{
	return sTexID;
}