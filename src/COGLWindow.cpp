#include "globals.hpp"

COGLWindow::COGLWindow():   sScreen_(NULL), sFullscreen_(true), sInitialized_(false), sLabel_("default")
{
	cout << "Powstaje COGLWindow" << endl;
}


COGLWindow::~COGLWindow()
{
	cout << "COGLWindow niszczony" << endl;
}

void COGLWindow::initOpenGL2D()
{	
	// Ustawienia wstêpne parametrów 
    glEnable(GL_TEXTURE_2D);

    //Inicjalizacja widoku 
    glViewport(0, 0, sScreen_->w, sScreen_->h);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

	//Tryb ortogonalny
    glOrtho(0.0, (GLdouble)sScreen_->w, (GLdouble)sScreen_->h, 0.0, 0.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
}



bool COGLWindow::createDisplay(int width, int height, int bpp, bool fullscreen, std::string label)
{
    Uint32 sdlFlags=SDL_INIT_VIDEO|SDL_INIT_TIMER;
    Uint32 vidFlags=0;
 	int okBPP = 1;
    int rgb_size[3];

    sFullscreen_ = fullscreen;
	sLabel_ = label;

    if(!sInitialized_)
    {
        assert(SDL_Init(sdlFlags)>=0);
    }

    if(sFullscreen_)
	{
		vidFlags |= SDL_FULLSCREEN;
	}
	// zrobiæ blok catch
    if(bpp != -1 && bpp != 8 && bpp != 15 && bpp != 16 && bpp != 24 && bpp !=32)
    {
		//try catch lub log
		bpp = -1;
		
    }
    else    //Dobór odpowiedniego bits per pixel
    {
        if(bpp == -1)
            bpp = SDL_GetVideoInfo()->vfmt->BitsPerPixel; 
		
		cout << bpp << endl;
		okBPP = SDL_VideoModeOK(width, height, bpp, vidFlags);
        cout << okBPP << endl;
		//assert(okBPP != 0);
		//asercja siê nie udaje jesli fullscreen jest realizowany dla nienominalnej rozdzielczosci ekranu
        
        if(okBPP != bpp)
        {
			//try catch lub log
            bpp = okBPP;
        }
    }
    //wymiar bufora
    switch(bpp)
    {
        case 8:
            rgb_size[0] = rgb_size[1] = 3;
            rgb_size[2] = 2;
            break;
        case 15:
        case 16:
            rgb_size[0] = rgb_size[1] = rgb_size[2] = 5;
            break;
        default:
            rgb_size[0] = rgb_size[1] = rgb_size[2] = 8;
            break;
    }

    //Ustawienie atrybutów OGL
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, rgb_size[0]);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, rgb_size[1]);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, rgb_size[2]);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, bpp==32 ? 24 : bpp);   
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 0);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE, 0);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE, 0);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE, 0);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE, 0);

    vidFlags |= SDL_OPENGL;

    //Ustawienia opisu okna
    if(!sInitialized_)    
    {
		SDL_WM_SetCaption(sLabel_.c_str(),sLabel_.c_str());
    }

    //Ustaw okno openGL poprzez SDL
    sScreen_ = SDL_SetVideoMode(width, height, bpp, vidFlags);

    if(!sScreen_) //w razie bledu opusc sdl
    {
        SDL_Quit();

        return false;
    }

	initOpenGL2D();

    return true;  
}

void COGLWindow::closeDisplay()
{
    if(sInitialized_)
    {
        SDL_Quit();
        sInitialized_ = false;
    }
}


void COGLWindow::update()
{
    SDL_GL_SwapBuffers();

	//Obsluzyc timer
}

void COGLWindow::clearDisplay(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha)
{
    glClearColor(red/255.0f,green/255.0f,blue/255.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
}


void COGLWindow::toggleFullscreen()
{
//SDL_WM_TF a linuksie
	createDisplay(sScreen_->w, sScreen_->h, sScreen_->format->BitsPerPixel, !sFullscreen_, sLabel_);    
// TODO: Obsluzyc przeladowanie obrazkow po zmianie trybu
}


SDL_Surface* COGLWindow::getDisplayPtr()
{
    return sScreen_;
}

bool COGLWindow::isInitialized()
{
    return sInitialized_;
}

int COGLWindow::getDisplayWidth()
{
    return sScreen_->w;
}

int COGLWindow::getDisplayHeight()
{
    return sScreen_->h;
}

int COGLWindow::getDisplayDepth()
{
    return sScreen_->format->BitsPerPixel;
}

bool COGLWindow::isFullscreen()
{
    return sFullscreen_;
}

