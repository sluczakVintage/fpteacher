/**\file
* @author Sebastian Luczak
* @date 2010.02.24
* @version 0.1
* @class CVideoOverlay CVideoOverlay.hpp
* @brief klasa CVideoOverlay 
*	
*/

#ifndef CVIDEOOVERLAY_H
#define CVIDEOOVERLAY_H

#include <boost/weak_ptr.hpp>
#include "CWorld.hpp"

class CVideoOverlay
{
	friend class CWorld;
public:
	CVideoOverlay()
	{
		uid_ = counter_;
		counter_++;
	};


	virtual bool drawIt() = 0;

	int getUID() const
	{
		return uid_;	
	};

protected:
	
	///
	int uid_;
	///
	static int counter_;

	///slaby wskaznik na siebie
	boost::shared_ptr<CVideoOverlay> selfPtr_;

};

#endif

//~~CDynamicObject.hpp
