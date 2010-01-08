#include "CMouseEvent.hpp"

CMouseEvent::CMouseEvent()
{
	pressedX_=0;
	pressedY_=0;
	releasedX_=0;
	releasedY_=0;
	cout << "CMouseEvent::CMouseEvent(): utworzono obiekt" << endl;
}

CMouseEvent::~CMouseEvent()
{
	cout << "CMouseEvent::CMouseEvent(): zniszczono obiekt" << endl;
}