/** @file CInput.cpp
* @author Rafal Malinowski
* @date 2009.12.07
* @version 0.6
* @brief klasa CInput odpowiada za odbieranie sygnalow z myszy i klawiatury
*	
*		
*/
#include "CInput.hpp"

using namespace std;

///wyzerowanie statycznego licznika
int CInput::licznik_obs=0;

///konstruktor domyslny
CInput::CInput()
{
	cout << "CInput::CInput(): rozmiar to " << KEY_MENU << endl;
	for( int i=0; i<rozmiar_tablicy; i++)
	{
		// wpisywanie wartosci 'u' do wszystkich komorek tablicy
		m_Keystates[i]='u';
	}
	cout << "CInput::CInput()" << endl;
	mouseClicked_ = false;

	MouseEvent.pressedX_ = 0;
	MouseEvent.pressedY_ = 0;
	MouseEvent.releasedX_ = 0;
	MouseEvent.releasedY_ = 0;
}

///destruktor
CInput::~CInput()
{
	cout << "CInput::~CInput()" << endl;
	observers_.clear();

}

///metoda mowiaca czy dany klawisz zostal wcisniety
///@param key kod klawisza o ktorego stan nastepuje pytanie
///@return true jesli klawisz jest wcisniety i false w przeciwnym wypadku
bool CInput::getKeyState(eKey key)
{
	if(m_Keystates[key] == 'd')
		{
			return true;
		}

		return false;
}

///metoda ktora kiedys bedzie zwracac wartosc wspolzednej X myszy
int CInput::getMouseX()
{
	return mouseX_;
}

///metoda ktora kiedys bedzie zwracac wartosc wspolzednej Y myszy
int CInput::getMouseY()
{
	return mouseY_;
}

///metoda ktora mowil czy mysz jest wcisnieta
bool CInput::mouseClicked()
{
	return mouseClicked_;
}

///metoda ktora przechwytuje zdarzenia z klawiatury i aktualizuje stan klawiszy
void CInput::update()
{
	SDL_Event event;

		while ( SDL_PollEvent( &event ) )
		{
			switch( event.type ) // w zaleznosci od rodzaju zdarzenia podejmowana jest odpowiednia akcja
			{

				case SDL_QUIT:	//wyjscie z programu
					break;
				case SDL_KEYDOWN:	//wcisniecie klawisz
					m_Keystates[event.key.keysym.sym] = 'd';
					cout << "CInput::update(): wcisnieto klawisz nr: " << event.key.keysym.sym << endl;
					break;
				case SDL_KEYUP:	//odcisniecie klawisz
					m_Keystates[event.key.keysym.sym] = 'u';
					break;
                case SDL_MOUSEMOTION:	//ruch myszy
					mouseX_ = event.motion.x;
					mouseY_ = event.motion.y;
			//		cout << "pozycja X myszy to: " << mouseX_ << endl;
			//		cout << "pozycja Y myszy to: " << mouseY_ << endl;
                    break;
                case SDL_MOUSEBUTTONUP:// odcisniecie myszy
						mouseClicked_ = false;
						MouseEvent.releasedX_ = mouseX_;
						MouseEvent.releasedY_ = mouseY_;
						refreshAll();
                    break;
                case SDL_MOUSEBUTTONDOWN:	//wcisniecie myszy
						mouseClicked_ = true;
						MouseEvent.pressedX_ = mouseX_;
						MouseEvent.pressedY_ = mouseY_;
                    break;
				default:
					break;
			}
		}
}

///metoda dodajaca observatora zainteresowanego akcjami zwiazanymi z mysza
///@param o referencja do obiektu klasy CMouseObserver (lub po niej dziedziczacego)
void CInput::addMouseObserver(CMouseObserver & o)
{
	observers_.insert(pair<int, CMouseObserver*> (licznik_obs, &o));	//dodanie nowego observatora
	licznik_obs++;	//zwiekszenie licznika observatorow
}

///metoda usuwajaca observatora zainteresowanego akcjami zwiazanymi z mysza
///@param o referencja do obiektu klasy CMouseObserver (lub po niej dziedziczacego)
void CInput::removeMouseObserver(CMouseObserver & o)
{
	//@todo zrobic sensowne usuwanie observatorow, poki co nie ma takiej potrzeby
}

///metoda wywolujace metode refresh we wszystkich observatorach akcji myszy
void CInput::refreshAll()
{
		CMouseEvent * tempMouseEvent = new CMouseEvent(); //stworzenie nowego obiektu ktory zostanie wyslany do observatorow
		///@todo przeciazyc operator = w CMouseEvent

		tempMouseEvent->pressedX_ = MouseEvent.pressedX_;	//przypisanie nowopowstalemu obiektowi CMouseEvent aktualnego stanu myszy
		tempMouseEvent->pressedY_ = MouseEvent.pressedY_;
		tempMouseEvent->releasedX_ = MouseEvent.releasedX_;
		tempMouseEvent->releasedY_ = MouseEvent.releasedY_;

		map<int, CMouseObserver*>::iterator it;

		for(it = observers_.begin(); it != observers_.end(); it++ ) //w petli tej CInput wywoluje funkcje refresh we wszystkich obserwatorach
																	// czyli klasach ktore dziedzicza po CMouseObserver
		{
			(*it).second->refresh(tempMouseEvent);
		}

		delete tempMouseEvent; //usuniecie niepotrzebnego juz obiektu tempMouseEvent, zapobiega wyciekom pamieci
}

//~~CInput.cpp
