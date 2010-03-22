/** @file CBalance.hpp
* @author Rafal Malinowski
* @date 2010.03.16
* @version 0.1
* @class CBalance CBalance.hpp
* @brief 
*  
*		
*/

#ifndef CBALANCE_H
#define CBALANCE_H

#include <string>

#include <boost/smart_ptr.hpp>

#include "utils.hpp"

#include "CVideoSystem.hpp"
#include "CStaticObject.hpp"
#include "CVideoOverlay.hpp"
#include "CAuditorium.hpp"
#include "CEntity.hpp"
#include "CLogic.hpp"
#include "Clog.hpp"
#include "CKeyObserver.hpp"
#include "CFontMgr.hpp"

using namespace utils;
using namespace logging;

class CKeyObserver;

class CBalance : public CVideoOverlay, CKeyObserver
{
public:

	CBalance();	
	~CBalance();

	virtual bool drawIt();

private:


	float x_;
	float y_;
	float a_;
	float v_;
	bool pressedLeft_;
	bool pressedRight_;
	boost::shared_ptr<CStaticObject> ball_;

	void moveBall();
	virtual void KeyPressed(SDLKey key, bool pressed);
};

#endif

//~~CSlider.hpp
