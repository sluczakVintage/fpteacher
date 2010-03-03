/** @file CGuiMenu.cpp
* @author Sebastian Luczak
* @date 2010.03.03
* @version 0.1
 
* @brief klasa CGuiMenu opisuje wysuwane menu wyboru akcji
*	
*/


#include "CGuiMenu.hpp"

using namespace std;


//konstruktor 
//@param trzy liczby float
CGuiMenu::CGuiMenu() : slideOut_(false), visible_(false), x_(1000.f), y_(200.f)
{
	menuBackground_ = boost::shared_ptr<CStaticObject>( new CStaticObject(x_, y_, 300.f, utils::PATH_GUI+"sliding_menu.png", 0, 0));
	CInput::getInstance()->addMouseObserver(*this, static_cast<int>(x_), static_cast<int>(x_+100), static_cast<int>(y_), static_cast<int>(y_+371) );
	moveObserver_=true;
	cout<<"CGuiMenu::CGuiMenu: tworzenie zakoñczone sukcesem"<<endl;
}

CGuiMenu::~CGuiMenu()
{
	cout<<"CGuiMenu::~CGuiMenu: niszczenie"<<endl;
}

void CGuiMenu::show()
{	
	slideOut_ = true;
}

void CGuiMenu::hide()
{	
	slideOut_ = false;
}

void CGuiMenu::refresh(CMouseEvent * CMO)
{

}

void CGuiMenu::drawIt()
{
	if(slideOut_)
	{///@todo Przerobic na stale (224, 800.f, 371.f itp)!!!
		if(x_ >= 800.f)
		{
			x_ = x_ - 10.f;
			menuBackground_->updatePosition(x_, y_);
		}
		else
		{
			//CInput::getInstance()->removeMouseObserver(*this);
			//CInput::getInstance()->addMouseObserver(*this, static_cast<int>(x_), static_cast<int>(x_+234), static_cast<int>(y_), static_cast<int>(y_+371) );
			visible_ = true;
		}
	}
	else
	{
		if(x_ < 1000.f)
		{
			x_ = x_ + 10.f;
			menuBackground_->updatePosition(x_, y_);
		}
		else
		{
			//CInput::getInstance()->removeMouseObserver(*this);
			//CInput::getInstance()->addMouseObserver(*this, static_cast<int>(x_), static_cast<int>(x_+100), static_cast<int>(y_), static_cast<int>(y_+371) );
			visible_ = false;
		}
	}
	
	menuBackground_->drawIt();

}

void CGuiMenu::mouseIsOver(bool over)
{
	if (over) show();
	else  hide();
	setMoveIsOver(over);
}

//~~CGuiMenu.cpp
