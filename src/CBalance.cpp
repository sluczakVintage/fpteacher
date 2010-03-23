/** @file CBalance.cpp
* @author Rafal Malinowski
* @date 2010.03.16
* @version 0.1
* @brief 
*  
*		
*/

#include "CBalance.hpp"



CBalance::CBalance()
{
	CLog::getInstance()->sss << "CBalance::CBalance(): Konstruktor CBalance"   << endl;
	logs(CLog::getInstance()->sss.str(), TEMP);
	CInput::getInstance()->addKeyObserver(*this);

	x_=400;
	y_=650;
	a_=0.05f;
	v_=0.01f;
	pressedLeft_=false;
	pressedRight_=false;
	ball_ = boost::shared_ptr<CStaticObject>( new CStaticObject(x_, y_, 310.f, utils::PATH_SPRITES_MINIGAMES_BALANCE+"ball.png", 0, 0));
	table_ = boost::shared_ptr<CStaticObject>( new CStaticObject(294, 660, 310.f, utils::PATH_SPRITES_MINIGAMES_BALANCE+"table.png", 0, 0));
}

CBalance::~CBalance()
{
	CLog::getInstance()->sss << "CBalance::~CBalance(): Destruktor CBalance"   << endl;
	logs(CLog::getInstance()->sss.str(), TEMP);
}



void CBalance::KeyPressed(SDLKey key, bool pressed)
{
	if(pressed && key == KEY_LEFT) 
	{
		pressedLeft_=true;
	}
	else if (!pressed && key == KEY_LEFT) 
	{
		pressedLeft_=false;
	}
	else if (pressed && key == KEY_RIGHT) 
	{
		pressedRight_=true;
	}
	else if (!pressed && key == KEY_RIGHT) 
	{
		pressedRight_=false;
	}
	else {};
}

void CBalance::moveBall()
{
	if (pressedLeft_) 
	{
		a_=a_-0.005f;
		if ( a_>= -0.01f && a_<= 0.01f) a_=a_-0.015f;
	}
	if (pressedRight_) 
	{
		a_=a_+0.005f;
		if ( a_>= -0.01f && a_<= 0.01f) a_=a_+0.015f;
	}
	v_=v_+a_;
	x_=x_+v_;
	y_=650+0.002f*(x_-400)*(x_-400);
	ball_->updatePosition(x_, y_);
}

bool CBalance::drawIt()
{
	moveBall();
	table_->drawIt();
	ball_->drawIt();
	return true;
}