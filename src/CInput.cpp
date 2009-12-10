//#include "CInput.hpp"
#include "globals.hpp"
#include "keys.hpp"

using namespace std;

CInput::CInput()
{
	for( int i=0; i<200; i++)
	{
		m_Keystates[i]=0;
	}
}

CInput::~CInput()
{
	//nic nie robi
}

int CInput::getKeyState(eKey key)
{
	if(m_Keystates[key] == 'd')
		{
			return 1;
		}

		return 0;
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

	cout <<"w update" << endl;
		while ( SDL_PollEvent( &event ) )
		{
			cout << "eloelo" << endl;
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
	cout <<"po update" << endl;
}