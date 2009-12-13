#include "CEngine.hpp"

using namespace std;

CEngine::CEngine()
{
	cout << "tworze CEngine";
}

CEngine::~CEngine()
{
	cout << "niszcze CEngine";
}

bool CEngine::init()
{
	//Odpala SDLa
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }
	//odpalenia singletonu inputa
	CInput* Input = CInput::getInstance();
	//odpalenia singletonu CWorld
	CWorld* CWorld = CWorld::getInstance();

	//odpalenia singletonu COGLa
	COGLWindow* window = COGLWindow::getInstance();
	COGLWindow::getInstance()->createDisplay();
	return true;
}

void CEngine::start()
{
	bool quit=false;
	while(!quit)
	{
		//odpalenie updatow wiekszosci klas
		CWorld::getInstance()->draw();
		CInput::getInstance()->update();
		COGLWindow::getInstance()->update();
		if(CInput::getInstance()->getKeyState(KEY_q) == 1) quit=true;
	}
}

void CEngine::end()
{
	//zamyka SDLa
	SDL_Quit();
	//niszczy singleton inputa
	CInput::destroyInstance();
	//zamyka okno
	COGLWindow::getInstance()->closeDisplay();
	//niszczy singleton COGLa
	COGLWindow::destroyInstance();
	//niszczy singleton CWorld
	CWorld::destroyInstance();
}