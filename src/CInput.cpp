#include "CInput.hpp"

using namespace std;

///konstruktor domyslny
CInput::CInput()
{
	for( int i=0; i<200; i++)
	{
		// wpisywanie wartosci 'u' do wszystkich komorek tablicy
		m_Keystates[i]='u';
	}
	cout << "CInput::CInput()" << endl;
}

///destruktor domyslny
CInput::~CInput()
{
	cout << "CInput::~CInput()" << endl;

}

///metoda mowiaca czy dany klawisz zostal wcisniety
bool CInput::getKeyState(eKey key)
{
	if(m_Keystates[key] == 'd')
		{
			return true;
		}

		return false;
}

int CInput::getMouseX()
{
	return mouseX_;
}

int CInput::getMouseY()
{
	return mouseY_;
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
					break;
				case SDL_KEYUP:
					m_Keystates[event.key.keysym.sym] = 'u';
					break;
                case SDL_MOUSEMOTION:
                   // m_MouseX = event.motion.x;
                   // m_MouseY = Singleton<cGraphics>::GetSingletonPtr()->GetHeight() - event.motion.y;
                    break;
                case SDL_MOUSEBUTTONUP:
						//do input core stuff here
                    break;
                case SDL_MOUSEBUTTONDOWN:
						//do input core stuff here
                    break;
				default:
					break;
			}
		}
}