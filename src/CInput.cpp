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
}

///destruktor domyslny
CInput::~CInput()
{
	cout << "CInput::~CInput()" << endl;

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
					mouseY_ = COGLWindow::getInstance()->getDisplayHeight() - event.motion.y;
					cout << "pozycja X myszy to: " << mouseX_ << endl;
                   	cout << "pozycja Y myszy to: " << mouseY_ << endl;
                    break;
                case SDL_MOUSEBUTTONUP:
						cout << "odcisnieto mysz!" << endl;
						mouseClicked_ = false;
                    break;
                case SDL_MOUSEBUTTONDOWN:
						cout << "wcisnieto mysz!" << endl;
						mouseClicked_ = true;
                    break;
				default:
					break;
			}
		}
}
