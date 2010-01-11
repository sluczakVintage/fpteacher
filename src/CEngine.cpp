/** @file CEngine.cpp
* @author Rafal Malinowski
* @date 2009.12.07
* @version 0.1_draft
* @brief klasa CEngine odpowiada za poprawne dzialanie silnika gry
*	
*		
*/

/// @FESTER -> Zmienilem CEntity na Static i Dynamic

#include "CEngine.hpp"

using namespace std;

///konstruktor domyslny
CEngine::CEngine()
{
	refresh_flag = false;
	// Ziarno dla funkcji pseudolosowej
	srand( static_cast<int>( SDL_GetTicks() ) );
	cout << "CEngine::CEngine(): konstruktor domyslny" << endl;
}


///destruktor
CEngine::~CEngine()
{
	cout << "CEngine::~CEngine(): niszczenie" << endl;
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
	
	//
	CStaticEntity* splash = new CStaticEntity(0,0,0,"../res/graphics/menu/splash.png");
	CWorld::getInstance()->draw();
	COGLWindow::getInstance()->update();
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
	//CAuditorium::getInstance()->init();
	// odpalenie singletonu gui
	CGui::getInstance()->initGui();
	//CAuditorium::getInstance()->init(true);
	//CAuditorium::getInstance()->seatNewStudent(4,1, 0);


	return true;
}

///metoda posiadajaca glowna petle programu
void CEngine::start()
{
	CMusic muza1;
	muza1.openFile("muzyka1", "../res/music/Track01.mp3");
	CSound dzwiek1;
	CSound dzwiek2;
	CSound dzwiek3;
	CSound dzwiek4;
	CSound dzwiek5;
	CSound dzwiek6;
	CSound dzwiek7;
	dzwiek1.openFile(1, "ziomek1", "../res/sounds/ziomek1.wav");
	dzwiek2.openFile(2, "normalny1", "../res/sounds/normalny1.wav");
	dzwiek3.openFile(3, "kujon1", "../res/sounds/kujon1.wav");
	dzwiek4.openFile(4, "ziomek2", "../res/sounds/ziomek2.wav");
	dzwiek5.openFile(5, "normalny2", "../res/sounds/normalny2.wav");
	dzwiek6.openFile(6, "kujon2", "../res/sounds/kujon2.wav");
	dzwiek7.openFile(7, "dzwonek", "../res/sounds/dzwonek.wav");
	bool quit=false;
	mouse_quit_flag_=false;
	refresh_flag=true;
	refresh_enable=false;
	int time;
	int time1;
	while(!quit)
	{
		if(mouse_quit_flag_) quit=true;
		time = CTimer::getInstance()->getTime();
		CInput::getInstance()->update();
		CWorld::getInstance()->draw();
		COGLWindow::getInstance()->update();
		CNetwork::getInstance()-> handleNetwork();
		if(CInput::getInstance()->getKeyState(KEY_q) == true) quit=true;
		//if(CInput::getInstance()->getKeyState(KEY_m) == true) CAudioSystem::getInstance()->play_music("muzyka1");
		//if(CInput::getInstance()->getKeyState(KEY_n) == true) CAudioSystem::getInstance()->pause_music("muzyka1");
		//if(CInput::getInstance()->getKeyState(KEY_b) == true) CAudioSystem::getInstance()->stop_music("muzyka1");
		if(CInput::getInstance()->getKeyState(KEY_s) == true) CAudioSystem::getInstance()->play_sound("ziomek1");
		//if(CInput::getInstance()->getKeyState(KEY_d) == true) CAudioSystem::getInstance()->play_sound("ziomek");
		if(CInput::getInstance()->getKeyState(KEY_z) == true) CAudioSystem::getInstance()->set_sound_position("ziomek1", 270, 128);
		if(CInput::getInstance()->getKeyState(KEY_x) == true) CAudioSystem::getInstance()->set_sound_position("ziomek1", 0, 0);
		if(CInput::getInstance()->getKeyState(KEY_c) == true) CAudioSystem::getInstance()->set_sound_position("ziomek1", 90, 220);
		//if(CInput::getInstance()->getKeyState(KEY_1) == true) CAuditorium::getInstance()->seatNewStudent((CTimer::getInstance()->getTime())%5,(CTimer::getInstance()->getTime())%8,(CTimer::getInstance()->getTime())%8);	
	//	if(CInput::getInstance()->getKeyState(KEY_2) == true) CNetwork::getInstance()-> handleNetwork();
		refresh_enable=false;
		
		
		
		
		time1 = CTimer::getInstance()->getTime()-time;
		if(time1<1000/utils::FPS)
			CTimer::getInstance()->delay((1000/utils::FPS) - time1);
		
		//SDL_Delay(1000/utils::FPS);
	}

}

///metoda odpowiedzialna za zamykanie SDLa oraz ewentualne aktywowanie destruktorow roznych klas
void CEngine::end()
{
	refresh_flag=false;
	//niszczy gui
	CGui::destroyInstance();
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
	//CTimer::destroyInstance();
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

void CEngine::setMouseQuitFlag(bool quit)
{
	mouse_quit_flag_=quit;
}

//~~CEngine.cpp