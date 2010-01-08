/** @file CEngine.cpp
* @author Rafal Malinowski
* @date 2009.12.07
* @version 0.1_draft
* @brief klasa CEngine odpowiada za poprawne dzia³anie silnika gry
*	
*		
*/

/// @FESTER -> Zmieni³em CEntity na Static i Dynamic

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
	COGLWindow* COGLWindow = COGLWindow::getInstance();
	COGLWindow::getInstance()->createDisplay();

	//odpalenie singletonu CVideoSystem
	CVideoSystem* CVideoSystem = CVideoSystem::getInstance();

	//odpalenie singletonu CAudioSystem
	CAudioSystem* CAudioSystem = CAudioSystem::getInstance();

	//odpalenie singletonu manager'a sprite'ow
	CSpriteMgr* SpriteMgr = CSpriteMgr::getInstance();

	//odpalenie singletonu manager'a animacji
	CAnimationMgr * CAnimationMgr = CAnimationMgr::getInstance();
 
	//odpalenie singletonu timer'a
	CTimer* timer = CTimer::getInstance();
	CTimer::getInstance()->addObserver(*this, 1000/utils::FPS);

	//odpalenie singletonu CAuditorium
	CAuditorium::getInstance()->initFromXml();
	//CAuditorium::getInstance()->init(true);
	//CAuditorium::getInstance()->seatNewStudent(4,1, 0);

	//new CDynamicEntity(208.0, 110.0, 12.0, "..\\res\\graphics\\sprites\\students\\animset_sit.dat");

	return true;
}

///metoda posiadajaca glowna petle programu
void CEngine::start()
{
	CMusic* muza1 = new CMusic("muzyka1", "..\\res\\music\\Track01.mp3");
	CMusic* muza2 = new CMusic("muzyka2", "..\\res\\music\\Track02.mp3");
	CSound* dzwiek = new CSound(1, "dzwiek1", "..\\res\\sounds\\Comic_Msg.wav");
	bool quit=false;
	refresh_flag=true;
	refresh_enable=false;
	while(!quit)
	{
		CInput::getInstance()->update();
		CWorld::getInstance()->draw();
		COGLWindow::getInstance()->update();
	//	CNetwork::getInstance()-> handleNetwork();
		if(CInput::getInstance()->getKeyState(KEY_q) == true) quit=true;
		if(CInput::getInstance()->getKeyState(KEY_m) == true) CAudioSystem::getInstance()->play_music("muzyka1");
		if(CInput::getInstance()->getKeyState(KEY_n) == true) CAudioSystem::getInstance()->pause_music("muzyka1");
		if(CInput::getInstance()->getKeyState(KEY_b) == true) CAudioSystem::getInstance()->stop_music("muzyka1");
		if(CInput::getInstance()->getKeyState(KEY_s) == true) CAudioSystem::getInstance()->play_sound("dzwiek1");
		if(CInput::getInstance()->getKeyState(KEY_z) == true) CAudioSystem::getInstance()->set_sound_position("dzwiek1", 270);
		if(CInput::getInstance()->getKeyState(KEY_x) == true) CAudioSystem::getInstance()->set_sound_position("dzwiek1", 0);
		if(CInput::getInstance()->getKeyState(KEY_c) == true) CAudioSystem::getInstance()->set_sound_position("dzwiek1", 90);
		//if(CInput::getInstance()->getKeyState(KEY_1) == true) new CDynamicEntity(410.0, 398.0, 45.0, "..\\res\\graphics\\sprites\\students\\animset_sit.dat");
		if(CInput::getInstance()->getKeyState(KEY_1) == true) CAuditorium::getInstance()->seatNewStudent((CTimer::getInstance()->getTime())%5,(CTimer::getInstance()->getTime())%8,(CTimer::getInstance()->getTime())%2);

		refresh_enable=false;
		SDL_Delay(1000/utils::FPS);
	}

}

///metoda odpowiedzialna za zamykanie SDLa oraz ewentualne aktywowanie destruktorow roznych klas
void CEngine::end()
{
	refresh_flag=false;
	//niszczy singleton inputa
	CInput::destroyInstance();
	// niszczy CAuditoirum
	CAuditorium::destroyInstance();
	//niszczy singleton CWorld
	CWorld::destroyInstance();
	//niszczy singleton CAudioSystem
	CAudioSystem::destroyInstance();
	//niszczy singleton managera zasobow
	CAnimationMgr::destroyInstance();
	//niszczy singleton managera zasobow
	CSpriteMgr::destroyInstance();
	//niszczy system wyswietlania
	CVideoSystem::destroyInstance();
	//zamyka okno
	COGLWindow::getInstance()->closeDisplay();
	//niszczy singleton COGLa
	COGLWindow::destroyInstance();
	//niszczy Timer
	CTimer::destroyInstance();
	//zamyka SDLa
	SDL_Quit(); 

}

/// metoda dziedziczona po obserwatorze CTimerObserver, decydujaca w ktorym momencie ma nastapic refresh aplikacji
void CEngine::refresh()
{
	if(refresh_flag)
	{
		refresh_enable=true;
	}

}
