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

#include "CVideoSystem.hpp"
#include "CStaticObject.hpp"
#include "CVideoOverlay.hpp"
#include "CAuditorium.hpp"
#include "CEntity.hpp"
#include "CLogic.hpp"
#include "Clog.hpp"

using namespace utils;
using namespace logging;


class CSlider : public CVideoOverlay
{
public:

	CSlider();	
	~CSlider();

	virtual bool drawIt();

private:

	float backgroundPosition_;
	float backgroundWidth_;
	float markerPosition_;
	float markerWidth_;
	bool markerRight_;

	boost::shared_ptr<CStaticObject> background_;
	boost::shared_ptr<CStaticObject> marker_;

};

#endif

//~~CSlider.hpp
