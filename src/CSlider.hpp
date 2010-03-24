/** @file CSlider.hpp
* @author Rafal Malinowski
* @date 2010.03.16
* @version 0.1
* @class CSlider CSlider.hpp
* @brief 
*  
*		
*/

#ifndef CSLIDER_H
#define CSLIDER_H

#include <string>

#include <boost/smart_ptr.hpp>

#include "utils.hpp"

//#include "CVideoSystem.hpp"
#include "CStaticObject.hpp"
#include "CVideoOverlay.hpp"
//#include "CAuditorium.hpp"
//#include "CEntity.hpp"
//#include "CLogic.hpp"
//#include "Clog.hpp"
#include "CKeyObserver.hpp"
//#include "CFontMgr.hpp"
#include "CAction.hpp"

using namespace utils;
using namespace logging;

class CKeyObserver;
class CStaticObject;

class CSlider : public CVideoOverlay, CKeyObserver
{
public:

	CSlider();	
	~CSlider();
	void initGame(CAction * host);
	virtual bool drawIt();

private:
	enum game {
		PLAYING=1,
		THE_BEST=2,
		GOOD=3,
		BAD=4} game_sign;

	void showSign(game text);

	float backgroundPosition_;
	float backgroundWidth_;

	float markerPosition_;
	float markerWidth_;
	bool markerRight_;
	
	float targetPosition_;
	float targetWidth_;

	bool playing_;

	CAction * host_;

	boost::shared_ptr<CStaticObject> background_;
	boost::shared_ptr<CStaticObject> marker_;
	boost::shared_ptr<CStaticObject> target_;

	virtual void KeyPressed(SDLKey key, bool pressed);
};

#endif

//~~CSlider.hpp
