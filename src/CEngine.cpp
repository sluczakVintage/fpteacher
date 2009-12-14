#include "CEngine.hpp"

using namespace std;

CEngine::CEngine()
{
	refresh_flag = false;
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

	CTimer::getInstance()->addObserver(*this, 1000);
	new CStaticEntity(1.0, 1.0, 0.0, "..\\res\\graphics\\sprites\\auditorium\\audmain01.png");
	new CStaticEntity(55.0, 583.0, 60.0, "..\\res\\graphics\\sprites\\auditorium\\audmid01.png");
	new CStaticEntity(65.0, 486.0, 50.0, "..\\res\\graphics\\sprites\\auditorium\\audmid02.png");
	new CStaticEntity(75.0, 390.0, 40.0, "..\\res\\graphics\\sprites\\auditorium\\audmid03.png");
	new CStaticEntity(84.0, 296.0, 30.0, "..\\res\\graphics\\sprites\\auditorium\\audmid04.png");
	new CStaticEntity(94.0, 203.0, 20.0, "..\\res\\graphics\\sprites\\auditorium\\audmid05.png");
	new CStaticEntity(102.0, 108.0, 10.0, "..\\res\\graphics\\sprites\\auditorium\\audmid06.png");

	new CStaticEntity(208.0, 110.0, 12.0, "..\\res\\graphics\\sprites\\students\\boy1.png");

	return true;
}

void CEngine::start()
{
	bool quit=false;
	refresh_flag=true;
	while(!quit)
	{
		CInput::getInstance()->update();
		CWorld::getInstance()->draw();
		COGLWindow::getInstance()->update();
		if(CInput::getInstance()->getKeyState(KEY_q) == true) quit=true;
		if(CInput::getInstance()->getKeyState(KEY_1) == true) new CStaticEntity(410.0, 398.0, 45.0, "..\\res\\graphics\\sprites\\students\\boy1.png");
		//if(CInput::getInstance()->getKeyState(KEY_2) == true) new CStaticEntity(150.0, 150.0, 1.0, "..\\res\\graphics\\sprites\\students\\boy1.png");
		//if(CInput::getInstance()->getKeyState(KEY_3) == true) new CStaticEntity(300.0, 150.0, 1.0, "..\\res\\graphics\\sprites\\students\\boy1.png");
			//new CStaticEntity(1.0, 1.0, 1.0, "..\\res\\graphics\\sprites\\students\\boy.png");
	}
}

void CEngine::end()
{
	refresh_flag=false;
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

void CEngine::refresh()
{
	if(refresh_flag)
	{
		//odpalenie updatow wiekszosci klas
		//CInput::getInstance()->update();
		//CWorld::getInstance()->draw();
		//COGLWindow::getInstance()->update();
		cout << "refresh dziala" << endl;
	}
}