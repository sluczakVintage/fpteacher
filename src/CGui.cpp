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

void CGui::refresh()
{
	cout << "zrobil sie refresh w GUI" << endl;
}