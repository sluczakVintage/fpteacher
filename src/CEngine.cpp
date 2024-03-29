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
	string siec;
	string kto;
	string add;
	cout<<"Podaj kim chcesz grac s/t\n>";
	cin>>kto;
	if(kto=="T" || kto=="t")
		CLogic::getInstance()->prefIsTeacher_ = true;
	else
		CLogic::getInstance()->prefIsTeacher_ = false;

	cout<<"Czy uruchomic rozgrywke sieciowa? T/N\n>";
	cin>>siec;	

	if(siec=="T" || siec == "t")
	{
		cout<<"Podaj adres sieciowy IPv4 komputera z ktorym chcesz sie polaczyc lub wpisz 0 dla localhost\n>";
		cin>>add;

		if(add=="0")
			CNetwork::getInstance()->initNetwork("127.0.0.1");
		else
			CNetwork::getInstance()->initNetwork(add.c_str());
		
	}
	else
	{
		CLogic::getInstance()->init(CLogic::getInstance()->prefIsTeacher_);
	}
//////////////////////////////~~~~
	
	//Odpala SDLa
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
		cout << "CEngine::init(): nie udalo sie uruchomic SDLa" << endl;
        return false;
    }

	//odpalenia singletonu CLog
	CLog * loga = CLog::getInstance();

	CLog::getInstance()->setLoggingOnConsole(true, false, false, true);

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

	CLogic::getInstance()->initActions();

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
	CFontMgr::getInstance()->buildFont("cartoon16B.png");

	CThrow * throwInstance = new CThrow(THROW_TEACHER);

	//CSlider * sliderInstance = new CSlider();
	//CBalance * balanceInstance = new CBalance();


	bool quit=false;
	mouse_quit_flag_=false;
	refresh_flag=true;
	refresh_enable=false;
	int time;
	int time1;



	CInput::getInstance()->removeMouseObserver(*CGui::getInstance());
	CInput::getInstance()->addMouseObserver(*CGui::getInstance(), 0, 10, 0, 10);
	CInput::getInstance()->removeMouseObserver(*CGui::getInstance());
	CInput::getInstance()->addMouseObserver(*CGui::getInstance(), 0, 10, 0, 10);
	CInput::getInstance()->removeMouseObserver(*CGui::getInstance());
	CInput::getInstance()->addMouseObserver(*CGui::getInstance(), 0, 10, 0, 10);
	CInput::getInstance()->removeKeyObserver(*CGui::getInstance());
	CInput::getInstance()->addKeyObserver(*CGui::getInstance());
	CInput::getInstance()->removeKeyObserver(*CGui::getInstance());
	CInput::getInstance()->addKeyObserver(*CGui::getInstance());
	///
	while(!quit)
	{
		if(mouse_quit_flag_) quit=true;
		time = CTimer::getInstance()->getTime();
		CInput::getInstance()->update();
		CWorld::getInstance()->draw();
		CGuiMenu::getInstance()->drawIt();
		//sliderInstance->drawIt();
		//balanceInstance->drawIt();
		CVideoSystem::getInstance()->drawMouseCursor();
		CLogic::getInstance()->performActions();

		//ROBOCZE
		CFontMgr::getInstance()->printText(30, 30, "Hello Font!", "default.png");
		CFontMgr::getInstance()->printText(50, 50, "Gruby czarny kot!", "cartoon16B");
		stringstream p,o,m;
		p<<CLogic::getInstance()->getMyPoints();
		o<<CLogic::getInstance()->getOpPoints();
		m<<CLogic::getInstance()->getMyMana();
		CFontMgr::getInstance()->printText(630, 15, ("Moje punkty: " + p.str()),"cartoon16B");
		CFontMgr::getInstance()->printText(630, 37, "Moja MANA: " + m.str(), "cartoon16B");

		CFontMgr::getInstance()->printText(630, 59, "Punkty przeciwnika: " + o.str(),"cartoon16B");
		
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
			throwInstance->setCThrowSource(CInput::getInstance()->getMouseX()+30, CInput::getInstance()->getMouseY()+40 );
			throwInstance->setCThrowDestination(CInput::getInstance()->getMouseX(), CInput::getInstance()->getMouseY() );
			throwInstance->finalizeCThrowInitiation();
		}
		///

		CVideoSystem::getInstance()->update();
		if(CInput::getInstance()->getKeyState(KEY_q) == true) quit=true;
		refresh_enable=false;  /// Co to jest za zmienna? Bo chyba ciagle jest false...
		
		time1 = CTimer::getInstance()->getTime()-time;
		if(time1<1000/utils::FPS)
			CTimer::getInstance()->delay((1000/utils::FPS) - time1);	
	}
	
	//delete sliderInstance;
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
	//niszczy CConstrants
	CConstants::getInstance()->destroyInstance();
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
