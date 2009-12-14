/** @file COGLWindow.cpp
* @author Sebastian £uczak
* @date 2009.12.08
* @version 0.2_draft
* @brief Klasa jest odpowiedzialna za inicjalizacje podsystemow SDL i OpenGL i utworzenie okna w 
*	wybranym trybie
*	
*/

#include "COGLWindow.hpp"

///Konstruktor domyslny
COGLWindow::COGLWindow():   sScreen_(NULL), sFullscreen_(false), sInitialized_(false), sLabel_("default")
{
	cout << "Powstaje COGLWindow" << endl;
}

///Destruktor domyslny
COGLWindow::~COGLWindow()
{
	cout << "COGLWindow niszczony" << endl;
}

///Metoda ustawiajaca wstepnie parametry i maszyne stanow OpenGL
void COGLWindow::initOpenGL2D()
{	
    //Inicjalizacja widoku 
    glViewport(0, 0, sScreen_->w, sScreen_->h);
	//Ustawienie koloru czyszczenia
	glClearColor(255.f, 255.f, 255.f, 0.f);
	//Wylaczenie testu bufora glebokosci 
	glDisable(GL_DEPTH_TEST);
	//Wylaczenie widocznosci obiektow zaslonietych (tryb2D)
    glDisable(GL_CULL_FACE);
	//Dodanie stanu przetwarzania tekstur 2D
    glEnable(GL_TEXTURE_2D);

	//Przelaczenie na przetwarzanie stosu obserwacji
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

	//Tryb ortogonalny
    glOrtho(0.0, (GLdouble)sScreen_->w, (GLdouble)sScreen_->h, 0.0, 0.0, 1.0);

	//Powrót do przetwarzania stosu modyfikacji
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
}


/// Metoda tworzaca okno gry zgodnie z podanymi paramterami
/// @return true jesli tworzenie okna sie powiodlo
bool COGLWindow::createDisplay(int width, int height, int bpp, std::string label, bool fullscreen) 
{
	/// @todo sprawdzic czy potrzebne jest przeladowywanie tekstur przy zmianie rozmiaru

    //Uint32 sdlFlags=SDL_INIT_VIDEO;
    Uint32 vidFlags=0;
 	int okBPP = 1;
    int rgb_size[3];

	sFullscreen_ = fullscreen;
	sLabel_ = label;

	// Dodac flage SDL jesli tryb pelnoekranowy
    if(sFullscreen_)
	{
		vidFlags |= SDL_FULLSCREEN;
	}
	/// @todo zrobic blok catch i log
	// jesli bpp nie pasuje do zadnego z domyslnych trybow ustaw na tryb automatyczny
    if(bpp != -1 && bpp != 8 && bpp != 16 && bpp != 24 && bpp !=32)
    {
		bpp = -1;
		
    }
    else    //Dobór odpowiedniego bits per pixel
    {
		if(bpp == -1)
            bpp = SDL_GetVideoInfo()->vfmt->BitsPerPixel; 
		
		//sprawdz czy podane parametry moga byc zastosowane na sprzecie
		okBPP = SDL_VideoModeOK(width, height, bpp, vidFlags);
		cout << "Sprawdzam, czy okno o podanych parametrach mozna wyswietlic " << endl;
		if(okBPP)
		{
			if(sFullscreen_)
				cout << "Fullscreen o parametrach" << endl;
			else
				cout << "Tryb okienkowy o parametrach" << endl;

			cout << " rozdzielczosc: " << width << " x " << height << endl;
			cout << " paleta barw: " << okBPP << endl;
			cout << " Test sie powiodl, okno zostanie wyswietlone " << endl;
		}
		else
		{
			/// @todo throw
			cout << "Test sie nie powiodl" << endl;
		}
        // jesli bpp zadeklarowane jest inne niz oferowane przez sprzet, zmien wybor
		///@todo okBPP == 0 musi zostac wczesniej wylapane i obsluzone
        if( okBPP != bpp )
        {
            bpp = okBPP;
        }
    }
    //ustalanie wymiaru buforów
    switch(bpp)
    {
        case 8:
            rgb_size[0] = rgb_size[1] = 3;
            rgb_size[2] = 2; 
            break;
        case 16:
            rgb_size[0] = rgb_size[1] = rgb_size[2] = 5;
            break;
        default:
            rgb_size[0] = rgb_size[1] = rgb_size[2] = 8;
            break;
    }

    //Ustawienie atrybutów SDL -> OGL
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, rgb_size[0]);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, rgb_size[1]);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, rgb_size[2]);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, bpp==32 ? 24 : bpp);   

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

/// Zamyka okno i opuszcza SDL
void COGLWindow::closeDisplay()
{
    if(sInitialized_)
    {
        sInitialized_ = false;
		SDL_Quit();
    }
}

/// Czysci ekran wybranym kolorem
void COGLWindow::clearDisplay(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha)
{
    glClearColor(red/255.0f,green/255.0f,blue/255.0f,0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
}

/// Zmienia tryb wyswietlania okno/fullscreen
void COGLWindow::toggleFullscreen()
{
//SDL_WM_TF a linuksie
	createDisplay(sScreen_->w, sScreen_->h, sScreen_->format->BitsPerPixel, sLabel_, !sFullscreen_);    
/// @todo Obsluzyc przeladowanie obrazkow po zmianie trybu
// zlapac jesli sie nie uda zmienic trybu
}

