#include "CSprite.hpp"

CSprite::CSprite() : 
	sSprite(new SDL_Surface),
	sAlpha(255)
{

   releaseSprite();
}


CSprite::CSprite(std::string filename) : 
    sSprite(new SDL_Surface),
    sAlpha(255)
{
   openFile(filename);
}

CSprite::~CSprite()
{
   std::cout<<"Destruktor CSpirte" <<std::endl;
   releaseSprite();
}

void CSprite::openFile(std::string filename)
{
	boost::shared_ptr<SDL_Surface> image = utils::LoadImage( filename.c_str() );
	if(image.get()){
		 std::cout<<"Obrazek "<< filename.c_str() << " zaladowano pomyslnie" <<std::endl;
		attachSprite(image);
		}
	else {
		 std::cerr<<"Nie zaladowano obrazka "<<IMG_GetError()<<std::endl;
		 std::cout<<"Nie zaladowano obrazka "<<IMG_GetError()<<std::endl;
	}

}

void CSprite::attachSprite(boost::shared_ptr<SDL_Surface> surface)
{
	utils::TexDims tex_dims;
	//na wszelki wypadek wyzeruj wszelkie parametry tekstury i sprite'a
	releaseSprite();		
    
	assert(surface.get()); //log!
	//przypisz wartosci do pol CSprite
	sWidth = static_cast<float>(surface->w);
	sHeight = static_cast<float>(surface->h);
	//przetworz SDL_Surface na teksture OGL

	sTexID = utils::SurfaceToTexture(surface, tex_dims);
	sTexDims = tex_dims;
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
	//utils::SafeFreeSurface(sSprite.get());  

    attachSprite(toReload);
}

void CSprite::releaseSprite()
{
    //przywróæ stan Sprite'a
    if(glIsTexture(sTexID))
        glDeleteTextures(1,&sTexID);
	sTexDims.texMaxX = sTexDims.texMaxY = sTexDims.texMinX = sTexDims.texMinY = 0.f;
    sTexID = 0;
    sWidth = sHeight = 0;
}

void CSprite::drawCSprite(int x, int y) const
{
    drawCSprite(static_cast<float>(x),static_cast<float>(y));
}

void CSprite::drawCSprite(float x, float y) const
{
	CVideoSystem::getInstance()->drawCSprite(x,y,*this);
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

utils::TexDims CSprite::getTexDimensions() const
{ 
	return sTexDims;
}