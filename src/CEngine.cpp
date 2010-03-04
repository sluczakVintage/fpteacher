/** @file CEngine.cpp
* @author Rafal Malinowski
* @date 2009.12.07
* @version 0.6
* @brief klasa CEngine odpowiada za poprawne dzialanie silnika gry
*	
*		
*/

/// @FESTER -> Zmienilem CEntity na Static i Dynamic

#include "CEngine.hpp"

using namespace std;
using namespace logging;

///konstruktor domyslny
CEngine::CEngine()
{
	refresh_flag = false;
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

	//odpalenia singletonu CLog
	CLog * loga = CLog::getInstance();


	//logs("jakis temp", TEMP);
	//log->error_stream<< "elo elo" << endl;
	//odpalenia singletonu inputa
	CInput* Input = CInput::getInstance();
	//odpalenia singletonu CWorld
	CWorld* CWorld = CWorld::getInstance();

	//odpalenia singletonu COGLa
	COGLWindow* COGLWindow = COGLWindow::getInstance();
	COGLWindow::getInstance()->createDisplay();

	//odpalenie singletonu CVideoSystem
	CVideoSystem* CVideoSystem = CVideoSystem::getInstance();
	
	// splash!
	CStaticEntity* splash = new CStaticEntity(0,0,0,"../res/graphics/menu/splash.png");
	CWorld::getInstance()->draw();
	CVideoSystem::getInstance()->update();

	//odpalenie CLogic
	CLogic* Logic = CLogic::getInstance();

	//odpalenie singletonu CAudioSystem
	CAudioSystem* CAudioSystem = CAudioSystem::getInstance();

	//odpalenie singletonu manager'a sprite'ow
	CSpriteMgr* SpriteMgr = CSpriteMgr::getInstance();

	//odpalenie singletonu manager'a animacji
	CAnimationMgr * CAnimationMgr = CAnimationMgr::getInstance();
 
	//odpalenie singletonu manager'a czcionek
	CFontMgr* CFontMgr = CFontMgr::getInstance();

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
	CGuiMenu* CGuiMenu = CGuiMenu::getInstance();


	return true;
}

///metoda posiadajaca glowna petle programu
void CEngine::start()
{

	CVideoSystem::getInstance()->loadCursor("chalk_idle_cursor0.dat", 18.f, 18.f);

	CMusic muza1;
	muza1.openFile("muzyka1", "../res/music/tlum.mp3");
	CSound dzwiek1;
	CSound dzwiek2;
	CSound dzwiek3;
	CSound dzwiek4;
	CSound dzwiek5;
	CSound dzwiek6;
	CSound dzwiek7;
	dzwiek1.openFile("ziomek1", "../res/sounds/ziomek1.wav");
	dzwiek2.openFile("normalny1", "../res/sounds/normalny1.wav");
	dzwiek3.openFile("kujon1", "../res/sounds/kujon1.wav");
	dzwiek4.openFile("ziomek2", "../res/sounds/ziomek2.wav");
	dzwiek5.openFile("normalny2", "../res/sounds/normalny2.wav");
	dzwiek6.openFile("kujon2", "../res/sounds/kujon2.wav");
	dzwiek7.openFile("dzwonek", "../res/sounds/dzwonek.wav");
	// Uruchom dzwiek na poczatku
	CAudioSystem::getInstance()->play_music("muzyka1");

	//ROBOCZE
	CFontMgr::getInstance()->buildFont("default.png");
	CFontMgr::getInstance()->buildFont("second.png");
	
	//boost::shared_ptr<CThrow> throwInstance (new CThrow);
	CThrow * throwInstance = new CThrow();
	//

	bool quit=false;
	mouse_quit_flag_=false;
	refresh_flag=true;
	refresh_enable=false;
	int time;
	int time1;
	int dupa=1;
	logs("jakis error", ERR);
	//logs(string("flaga quit to")+string(static_cast<char>(dupa)), INFO);
	logs("jakies info", INFO);
	logs("jakis error1", ERR);
	logs("jakis error2", ERR);
	logs("jakies info1", INFO);
	logs("jakis warning", WARNING);

	while(!quit)
	{
		if(mouse_quit_flag_) quit=true;
		time = CTimer::getInstance()->getTime();
		CInput::getInstance()->update();
		CWorld::getInstance()->draw();
		CGuiMenu::getInstance()->drawIt();
		CVideoSystem::getInstance()->drawMouseCursor();

		//ROBOCZE
		CFontMgr::getInstance()->printText(30, 30, "Hello Font!", "default.png");
		CFontMgr::getInstance()->printText(50, 50, "Gruby czarny kot!", "second");
		//
		CNetwork::getInstance()-> handleNetwork();
		/// ROBOCZE
		if(CInput::getInstance()->getKeyState(KEY_f) == true) 
		{
			COGLWindow::getInstance()->toggleFullscreen();
		}
		///
		
		/// ROBOCZE
		if(CInput::getInstance()->getKeyState(KEY_t) == true) 
		{
			throwInstance->setCThrowSource(CInput::getInstance()->getMouseX()+30, CInput::getInstance()->getMouseY()+40, 100);
			throwInstance->setCThrowDestination(CInput::getInstance()->getMouseX(), CInput::getInstance()->getMouseY(), 20);
			throwInstance->finalizeCThrowInitiation();
		}
		///
		/// ROBOCZE
		if(CInput::getInstance()->getKeyState(KEY_d) == true) 
		{
			CLogic::getInstance()->performAction("CTestAction");
		}
		//~
		CVideoSystem::getInstance()->update();
		if(CInput::getInstance()->getKeyState(KEY_q) == true) quit=true;
		refresh_enable=false;  /// Co to jest za zmienna? Bo chyba ciagle jest false...
		
		time1 = CTimer::getInstance()->getTime()-time;
		if(time1<1000/utils::FPS)
			CTimer::getInstance()->delay((1000/utils::FPS) - time1);	
	}
	
}

///metoda odpowiedzialna za zamykanie SDLa oraz ewentualne aktywowanie destruktorow roznych klas
void CEngine::end()
{
	refresh_flag=false;

	CGuiMenu::destroyInstance();
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
	//niszczy singleton managera czcionek teksturowych
	CFontMgr::destroyInstance();
	//niszczy singleton managera zasobow
	CAnimationMgr::destroyInstance();
	//niszczy singleton managera zasobow
	CSpriteMgr::destroyInstance();
	//niszczy system logiki gry
	CLogic::destroyInstance();
	//niszczy system wyswietlania
	CVideoSystem::destroyInstance();
	//zamyka okno
	COGLWindow::getInstance()->closeDisplay();
	//niszczy singleton COGLa
	COGLWindow::destroyInstance();

	//niszczy CLog
	CLog::destroyInstance();
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
