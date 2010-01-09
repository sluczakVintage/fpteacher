#include "CGui.hpp"
using namespace std;

CGui::CGui()
{

}

CGui::~CGui()
{

}

void CGui::initGui()
{
	cout << "				CGui::initGui():wszystko w porzadku" << endl;
	CInput::getInstance()->addMouseObserver(*this);

	new CStaticEntity(350.0, 20.0, 100.0, "..\\res\\graphics\\sprites\\gui\\play.png");
	new CStaticEntity(475.0, 20.0, 100.0, "..\\res\\graphics\\sprites\\gui\\pause.png");
	new CStaticEntity(600.0, 20.0, 100.0, "..\\res\\graphics\\sprites\\gui\\stop.png");
}

void CGui::refresh(CMouseEvent * CMO)
{
	//cout << "zrobil sie refresh w GUI," << endl;
	//cout << "wspolzedna x wcisniecia wynosi " << CMO->pressedX_;
	//cout << ", wspolzedna y wcisniecia wynosi " << CMO->pressedY_;
	//cout << "wspolzedna x wycisniecia wynosi " << CMO->releasedX_;
	//cout << ",a wspolzedna y wcisniecia wynosi " << CMO->releasedY_ << endl;

	if(	CMO->pressedX_<425 && CMO->pressedX_>350 && CMO->pressedY_<95 && CMO->pressedY_>20 && CMO->releasedX_<425 && CMO->releasedX_>350 && CMO->releasedY_<95 && CMO->releasedY_>20)
	{
		CAudioSystem::getInstance()->play_music("muzyka1");
	}
	else if (	CMO->pressedX_<550 && CMO->pressedX_>475 && CMO->pressedY_<95 && CMO->pressedY_>20 && CMO->releasedX_<550 && CMO->releasedX_>475 && CMO->releasedY_<95 && CMO->releasedY_>20)
	{
		CAudioSystem::getInstance()->pause_music("muzyka1");
	}
	else if (	CMO->pressedX_<675 && CMO->pressedX_>600 && CMO->pressedY_<95 && CMO->pressedY_>20 && CMO->releasedX_<675 && CMO->releasedX_>600 && CMO->releasedY_<95 && CMO->releasedY_>20)
	{
		CAudioSystem::getInstance()->stop_music("muzyka1");
	}
	else
	{
		//cout << "		nie trafiles cwoku!!" << endl;
	}
}