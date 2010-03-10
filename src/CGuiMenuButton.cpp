/** @file CGuiMenuButton.cpp
* @author Sebastian Luczak
* @date 2010.03.03
* @version 0.1
 
* @brief klasa CGuiMenuButton opisuje przycisk w wysuwanym menu wyboru akcji
*	
*/

#include "CGuiMenuButton.hpp"

using namespace std;
using namespace logging;

CGuiMenuButton::CGuiMenuButton( const float x, const float y, const int action, const int cost, string spritename) : x_(x), xOffset_(0.f), y_(y), action_(action), cost_(cost), visible_(false), pressed_(false)
{
	defaultSprite_ = boost::shared_ptr<CStaticObject>( new CStaticObject(x_, y_, 301.f, utils::PATH_GUI_BUTTONS+spritename, 0, 0));
	spritename.insert(spritename.find_last_of("."),"_pressed");
	onPressedSprite_ = boost::shared_ptr<CStaticObject>( new CStaticObject(x_, y_, 301.f, utils::PATH_GUI_BUTTONS+spritename, 0, 0));
	
	setId();
	//CInput::getInstance()->addMouseObserver(*this, static_cast<int>(x_), static_cast<int>(x_+70), static_cast<int>(y_), static_cast<int>(y_+70) );
	moveObserver_ = true;
	
	CLog::getInstance()->sss << "CGuiMenuButton::CGuiMenuButton: tworzenie zakonczone sukcesem" << endl;
	logs(CLog::getInstance()->sss.str(), INFO);
}

CGuiMenuButton::~CGuiMenuButton()
{
	CLog::getInstance()->sss << "CGuiMenuButton::CGuiMenuButton: zniszczenie" << endl;
	logs(CLog::getInstance()->sss.str(), INFO);
}

void CGuiMenuButton::show( const float x_off )
{
	xOffset_ = x_off;
	visible_ = true;
	CInput::getInstance()->addMouseObserver(*this, static_cast<int>(x_ + xOffset_), static_cast<int>(x_ + xOffset_ +70), static_cast<int>(y_), static_cast<int>(y_ + 70) );
}

void CGuiMenuButton::hide()
{
	visible_ = false;
	CInput::getInstance()->removeMouseObserver(*this);
}

void CGuiMenuButton::drawIt()
{
	if(visible_)
	{
		if(pressed_)
		{
			onPressedSprite_->updatePosition(x_ + xOffset_, y_);
			onPressedSprite_->drawIt();
			pressed_ = false;
		}
		else
		{
			defaultSprite_->updatePosition(x_ + xOffset_, y_);
			defaultSprite_->drawIt();
		}
	}
}


void CGuiMenuButton::refresh(CMouseEvent * CMO)
{
	pressed_ = true;
	CLog::getInstance()->sss << "CGuiMenuButton::CGuiMenuButton: Przycisniety" << endl;
	logs(CLog::getInstance()->sss.str(), TEMP);

}

void CGuiMenuButton::mouseIsOver(bool over)
{
	if (over) 
	{
		CLog::getInstance()->sss << "CGuiMenuButton::CGuiMenuButton: Nad przyciskiem" << endl;
		logs(CLog::getInstance()->sss.str(), TEMP);
	}
	else  
	{
		CLog::getInstance()->sss << "CGuiMenuButton::CGuiMenuButton: opuszczone" << endl;
		logs(CLog::getInstance()->sss.str(), TEMP);
	}
	setMoveIsOver(over);
}
//~~CGuiMenuButton.cpp
