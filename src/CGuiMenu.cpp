/** @file CGuiMenu.cpp
* @author Sebastian Luczak
* @date 2010.03.03
* @version 0.1
 
* @brief klasa CGuiMenu opisuje wysuwane menu wyboru akcji
*	
*/


#include "CGuiMenu.hpp"

using namespace std;
using namespace logging;


//konstruktor 
//@param trzy liczby float
CGuiMenu::CGuiMenu() : slide_(boost::logic::indeterminate), visible_(false), x_(1000.f), y_(200.f)
{
	menuBackground_ = boost::shared_ptr<CStaticObject>( new CStaticObject(x_, y_, 300.f, utils::PATH_GUI+"sliding_menu.png", 0, 0));
	//inicjalizacja obserwatora myszy
	setId();
	CInput::getInstance()->addMouseObserver(*this, static_cast<int>(x_), static_cast<int>(x_+100), static_cast<int>(y_), static_cast<int>(y_+371) );
	moveObserver_=true;
	
	//siatka przyciskow --> do wyciagania z pliku konf
	//for(int x = 0; x < 2; x++)
	//	for(int y = 0; y < 4; y++)
	//		Pobierz jaka akcja, koszt i grafika
	//		CGuiMenuButton(52 + ( x * 90 ), y_ + 45 + ( y * 75 ), AKCJA, KOSZT, SPRITENAME);
	
	buttons_.push_back(boost::shared_ptr<CGuiMenuButton>(new CGuiMenuButton(52, y_ + 45, 0, 20, "teach_chalk.png")));
	
	CLog::getInstance()->sss << "CGuiMenu::CGuiMenu: tworzenie zakonczone sukcesem" << endl;
	logs(CLog::getInstance()->sss.str(), INFO);
}

CGuiMenu::~CGuiMenu()
{
	CLog::getInstance()->sss << "CGuiMenu::~CGuiMenu: niszczenie" << endl;
	logs(CLog::getInstance()->sss.str(), INFO);
}

void CGuiMenu::show()
{	
	slide_ = true;
}

void CGuiMenu::hide()
{	
	slide_ = false;
	BOOST_FOREACH( boost::shared_ptr<CGuiMenuButton> button, buttons_ )
	{
		button->hide();
	}
}

void CGuiMenu::refresh(CMouseEvent * CMO)
{
	//puste
}

void CGuiMenu::drawIt()
{
	if(slide_)
	{///@todo Przerobic na stale (224, 800.f, 371.f itp)!!!
		visible_ = false;
		if(x_ >= 800.f)
		{
			x_ = x_ - 10.f;
			menuBackground_->updatePosition(x_, y_);
			CInput::getInstance()->removeMouseObserver(*this);
			CInput::getInstance()->addMouseObserver(*this, static_cast<int>(x_), static_cast<int>(x_+234), static_cast<int>(y_), static_cast<int>(y_+371) );
		}
		else
		{
			visible_ = true;
			BOOST_FOREACH( boost::shared_ptr<CGuiMenuButton> button, buttons_ )
			{
				button->show(x_);
			}
		}
	}
	else if(!slide_)
	{
		visible_ = false;
		if(x_ < 1000.f)
		{
			x_ = x_ + 10.f;
			menuBackground_->updatePosition(x_, y_);
			CInput::getInstance()->removeMouseObserver(*this);
			CInput::getInstance()->addMouseObserver(*this, static_cast<int>(x_), static_cast<int>(x_+100), static_cast<int>(y_), static_cast<int>(y_+371) );
		}
	}

	menuBackground_->drawIt();
	
	if(visible_)
	{
		slide_ = boost::logic::indeterminate;
		BOOST_FOREACH( boost::shared_ptr<CGuiMenuButton> button, buttons_ )
		{
			button->drawIt();
		}
	}
}

void CGuiMenu::mouseIsOver(bool over)
{
	if (over) 
		show();
	else  
		hide();
	setMoveIsOver(over);
}

//~~CGuiMenu.cpp
