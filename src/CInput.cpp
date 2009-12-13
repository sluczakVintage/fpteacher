#include "CInput.hpp"

using namespace std;

CInput::CInput()
{
	for( int i=0; i<200; i++)
	{
		m_Keystates[i]='u';
	}
	cout << "konstruktor CInput" << endl;
}

CInput::~CInput()
{
	cout << "destruktor CInput" << endl;

}

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