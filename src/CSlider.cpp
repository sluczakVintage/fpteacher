/** @file CSlider.cpp
* @author Rafal Malinowski
* @date 2010.03.16
* @version 0.1
* @brief 
*  
*		
*/

#include "CSlider.hpp"



CSlider::CSlider()
{
	CLog::getInstance()->sss << "CSlider::CSlider(): Konstruktor CSlider"   << endl;
	logs(CLog::getInstance()->sss.str(), TEMP);
	CInput::getInstance()->addKeyObserver(*this);

	background_ = boost::shared_ptr<CStaticObject>( new CStaticObject(50, 650, 310.f, utils::PATH_SPRITES_MINIGAMES_SLIDER+"slider.png", 0, 0));
	marker_ = boost::shared_ptr<CStaticObject>( new CStaticObject(50, 650, 300.f, utils::PATH_SPRITES_MINIGAMES_SLIDER+"marker.png", 0, 0));
	target_ = boost::shared_ptr<CStaticObject>( new CStaticObject(180, 650, 300.f, utils::PATH_SPRITES_MINIGAMES_SLIDER+"target.png", 0, 0));

	backgroundPosition_=50;
	backgroundWidth_=200;

	targetPosition_=180;
	targetWidth_=10;

	markerPosition_=50;
	markerWidth_=5;
	markerRight_=true;

	playing_=true;
	game_sign = PLAYING;
}

CSlider::~CSlider()
{
	CLog::getInstance()->sss << "CSlider::CSlider(): Destruktor CSlider"   << endl;
	logs(CLog::getInstance()->sss.str(), TEMP);
}

void CSlider::initGame(CAction * host)
{
	playing_=true;
	markerPosition_=50;
	markerRight_=true;
	host_=host;
}

bool CSlider::drawIt()
{
	
	if(markerRight_)
	{
		if ( (markerPosition_+markerWidth_) >= (backgroundPosition_+backgroundWidth_) ) markerRight_=false;
		else if(playing_)
		{
			markerPosition_=markerPosition_+3;
			marker_->updatePosition(markerPosition_, 650);
		}
	}
	else
	{
		if ( (markerPosition_) <= (backgroundPosition_) ) markerRight_=true;
		else if(playing_)
		{
			markerPosition_=markerPosition_-3;
			marker_->updatePosition(markerPosition_, 650);
		}
	}

	background_->drawIt();
	target_->drawIt();
	marker_->drawIt();

	showSign(game_sign);
	return true;
}

void CSlider::KeyPressed(SDLKey key, bool pressed)
{

	if(pressed && key == KEY_SPACE)
	{
		if(playing_) 
		{
			playing_=false;
			if ( (markerPosition_ > targetPosition_) && ( (markerPosition_+markerWidth_) < (targetPosition_+targetWidth_) ) )
			{
				CLog::getInstance()->sss << "BRAWO!! " << KEY_MENU << endl;
				logs(CLog::getInstance()->sss.str(), TEMP);
				game_sign = THE_BEST;
			}
			else if ( ( ( (markerPosition_+markerWidth_) > targetPosition_) && (markerPosition_<= targetPosition_ ) ) || ( ( markerPosition_ < (targetPosition_+targetWidth_) ) && ( (markerPosition_+markerWidth_) >= (targetPosition_+targetWidth_) ) ) ) 
			{
				CLog::getInstance()->sss << "prawie ;)" << KEY_MENU << endl;
				logs(CLog::getInstance()->sss.str(), TEMP);
				game_sign = GOOD;
			}
			else 
			{
				CLog::getInstance()->sss << "masakra... " << KEY_MENU << endl;
				logs(CLog::getInstance()->sss.str(), TEMP);
				game_sign = BAD;
			}
		}
		else 
		{
			playing_=true;
			game_sign = PLAYING;
		}
	}
}

void CSlider::showSign(game text)
{
	switch(text)
	{
	case PLAYING:
		CFontMgr::getInstance()->printText(50, 600, "dajesz!", "cartoon16B");
		break;
	case THE_BEST:
		CFontMgr::getInstance()->printText(50, 600, "Brawo!!", "cartoon16B");
		break;
	case GOOD:
		CFontMgr::getInstance()->printText(50, 600, "Niezle", "cartoon16B");
		break;
	case BAD:
		CFontMgr::getInstance()->printText(50, 600, "masakra...", "cartoon16B");
		break;
	default:
		break;
	}
}