/** @file CInput.cpp
* @author Rafal Malinowski
* @date 2009.12.07
* @version 0.1_draft
* @brief klasa CInput odpowiada za odbieranie sygna³ów z myszy i klawiatury
*	
*		
*/
#include "CInput.hpp"

using namespace std;


int CInput::licznik_obs=1;

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

///destruktor domyslny
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
			switch( event.type )
			{

				case SDL_QUIT:
					break;
				case SDL_KEYDOWN:
					m_Keystates[event.key.keysym.sym] = 'd';
					cout << "CInput::update(): wcisnieto klawisz nr: " << event.key.keysym.sym << endl;
					break;
				case SDL_KEYUP:
					m_Keystates[event.key.keysym.sym] = 'u';
					break;
                case SDL_MOUSEMOTION:
					mouseX_ = event.motion.x;
					mouseY_ = event.motion.y;
					//mouseY_ = COGLWindow::getInstance()->getDisplayHeight() - event.motion.y;
					cout << "pozycja X myszy to: " << mouseX_ << endl;
                   	cout << "pozycja Y myszy to: " << mouseY_ << endl;
                    break;
                case SDL_MOUSEBUTTONUP:
						cout << "odcisnieto mysz!" << endl;
						mouseClicked_ = false;
						MouseEvent.releasedX_ = mouseX_;
						MouseEvent.releasedY_ = mouseY_;
						refreshAll();
                    break;
                case SDL_MOUSEBUTTONDOWN:
						cout << "wcisnieto mysz!" << endl;
						mouseClicked_ = true;
						MouseEvent.pressedX_ = mouseX_;
						MouseEvent.pressedY_ = mouseY_;
                    break;
				default:
					break;
			}
		}
}


void CInput::addMouseObserver(CMouseObserver & o)
{
	observers_.insert(pair<int, CMouseObserver*> (licznik_obs, &o));
	cout << "					dodano observera" << endl;
	//o.refresh();
	licznik_obs++;
}

void CInput::removeMouseObserver(CMouseObserver & o)
{

}

void CInput::refreshAll()
{
		cout << "jestesmy w refreshAll" << endl;
		CMouseEvent * tempMouseEvent = new CMouseEvent();

		///@todo przeciazyc operator = w CMouseEvent

		tempMouseEvent->pressedX_ = MouseEvent.pressedX_;
		tempMouseEvent->pressedY_ = MouseEvent.pressedY_;
		tempMouseEvent->releasedX_ = MouseEvent.releasedX_;
		tempMouseEvent->releasedY_ = MouseEvent.releasedY_;

		map<int, CMouseObserver*>::iterator it;
		for(it = observers_.begin(); it != observers_.end(); it++ )
		{
			//it = observers_.begin();
			cout << "numer klucza" << (*it).first << endl;
			(*it).second->refresh(tempMouseEvent);
		}
}