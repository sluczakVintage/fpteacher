#include "CEngine.hpp"

using namespace std;
	///konstruktor domyslny
CEngine::CEngine()
{
	refresh_flag = false;
	cout << "CEngine::CEngine()" << endl;
}

	///destruktor domyslny
CEngine::~CEngine()
{
	cout << "CEngine::~CEngine()" << endl;
}

	///metoda w ktorej odpalany jest sdl, oraz uruchamiane sa konstruktory wielu klas (COGLWindow, CInput itd...)
bool CEngine::init()
{
	//Odpala SDLa
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
		cout << "CEngine::init(): nie udalo sie uruchomic SDLa" << endl;
        return false;
    }
	//odpalenia singletonu inputa
	CInput* Input = CInput::getInstance();
	//odpalenia singletonu CWorld
	CWorld* CWorld = CWorld::getInstance();

	//odpalenia singletonu COGLa
	COGLWindow* window = COGLWindow::getInstance();
	COGLWindow::getInstance()->createDisplay();

	CAudioSystem* CAudioSystem = CAudioSystem::getInstance();

	CTimer* timer = CTimer::getInstance();
	CTimer::getInstance()->addObserver(*this, 1000/utils::FPS);

	new CStaticEntity(1.0, 1.0, 0.0, "..\\res\\graphics\\sprites\\auditorium\\audmain01.png");
	new CStaticEntity(55.0, 583.0, 60.0, "..\\res\\graphics\\sprites\\auditorium\\audmid01.png");
	new CStaticEntity(65.0, 486.0, 50.0, "..\\res\\graphics\\sprites\\auditorium\\audmid02.png");
	new CStaticEntity(75.0, 390.0, 40.0, "..\\res\\graphics\\sprites\\auditorium\\audmid03.png");
	new CStaticEntity(84.0, 296.0, 30.0, "..\\res\\graphics\\sprites\\auditorium\\audmid04.png");
	new CStaticEntity(94.0, 203.0, 20.0, "..\\res\\graphics\\sprites\\auditorium\\audmid05.png");
	new CStaticEntity(102.0, 108.0, 10.0, "..\\res\\graphics\\sprites\\auditorium\\audmid06.png");

	new CStaticEntity(208.0, 110.0, 12.0, "..\\res\\graphics\\sprites\\students\\boy1.png");

	//if(Mix_OpenAudio(22050, AUDIO_S16, 2, 512)) {
 //   cout <<"Unable to open audio!\n" << endl << endl;
	//cout << Mix_GetError() << endl << endl;
	// }
	//new CStaticEntity(308.0, 110.0, 12.0, "dupa.png");
	return true;
}

	///metoda posiadajaca glowna petle programu
void CEngine::start()
{
	//if(Mix_OpenAudio(22050, AUDIO_S16, 2, 512)) {
 //   cout <<"Unable to open audio!\n" << endl << endl;
	//cout << Mix_GetError() << endl << endl;
	// }
	//CMusic Muzyka("Track01.mp3");
	//int audio_rate = 22050;
	//Uint16 audio_format = AUDIO_S16; /* 16-bit stereo */
	//int audio_channels = 2;
	//int audio_buffers = 512;
	new CMusic("muzyka1", "..\\res\\music\\Track01.mp3");
	new CMusic("muzyka2", "..\\res\\music\\Track02.mp3");
	bool quit=false;
	refresh_flag=true;
	refresh_enable=false;
	while(!quit)
	{
		//if(refresh_enable)
		//
			CInput::getInstance()->update();
			CWorld::getInstance()->draw();
			COGLWindow::getInstance()->update();
			if(CInput::getInstance()->getKeyState(KEY_q) == true) quit=true;
			if(CInput::getInstance()->getKeyState(KEY_m) == true) CAudioSystem::getInstance()->play_music("muzyka1");
			if(CInput::getInstance()->getKeyState(KEY_n) == true) CAudioSystem::getInstance()->pause_music("muzyka1");
			//if(CInput::getInstance()->getKeyState(KEY_x) == true) Muzyka.Pause();
			//if(CInput::getInstance()->getKeyState(KEY_c) == true) Muzyka.Stop();
			if(CInput::getInstance()->getKeyState(KEY_1) == true) new CStaticEntity(410.0, 398.0, 45.0, "..\\res\\graphics\\sprites\\students\\boy1.png");
			//Sleep(10);
			//cout << "CEngine::start()" << endl;
			refresh_enable=false;
			SDL_Delay(1000/utils::FPS);
		//}
	}
}

	///metoda odpowiedzialna za zamykanie SDLa oraz ewentualne aktywowanie destruktorow roznych klas
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

	/// metoda dziedziczona po obserwatorze CTimerObserver, decydujaca w ktorym momencie ma nastapic refresh aplikacji
void CEngine::refresh()
{
	if(refresh_flag)
	{
		refresh_enable=true;
		//cout << "CEngine::refresh(): chodz poki co nie wiadomo po co" << endl;
	}
}
