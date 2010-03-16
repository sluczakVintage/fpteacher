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

	background_ = boost::shared_ptr<CStaticObject>( new CStaticObject(50, 650, 310.f, utils::PATH_SPRITES_MINIGAMES+"slider/slider.png", 0, 0));
	marker_ = boost::shared_ptr<CStaticObject>( new CStaticObject(50, 650, 300.f, utils::PATH_SPRITES_MINIGAMES+"slider/marker.png", 0, 0));
	
	backgroundPosition_=50;
	backgroundWidth_=200;
	markerPosition_=50;
	markerWidth_=10;
	markerRight_=true;
}

CSlider::~CSlider()
{
	CLog::getInstance()->sss << "CSlider::CSlider(): Destruktor CSlider"   << endl;
	logs(CLog::getInstance()->sss.str(), TEMP);
}

bool CSlider::drawIt()
{
	
	if(markerRight_)
	{
		if ( (markerPosition_+markerWidth_) >= (backgroundPosition_+backgroundWidth_) ) markerRight_=false;
		else 
		{
			markerPosition_=markerPosition_+3;
			marker_->updatePosition(markerPosition_, 650);
		}
	}
	else
	{
		if ( (markerPosition_) <= (backgroundPosition_) ) markerRight_=true;
		else 
		{
			markerPosition_=markerPosition_-3;
			marker_->updatePosition(markerPosition_, 650);
		}
	}

	background_->drawIt();
	marker_->drawIt();
	return true;
}