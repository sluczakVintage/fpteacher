/** @file CThrow.hpp
* @author Sebastian luczak
* @date 2010.02.23
* @version 0.1
* @class CThrow CThrow.hpp
* @brief 
*  
*		
*/

#ifndef CTHROW_H
#define CTHROW_H

#include <string>

#include <boost/smart_ptr.hpp>

#include "utils.hpp"

#include "CVideoSystem.hpp"
#include "CDynamicObject.hpp"
#include "CVideoOverlay.hpp"
#include "CAuditorium.hpp"
#include "CEntity.hpp"


using namespace utils;



class CThrow : public CVideoOverlay
{
public:

	CThrow( const int type, const int object = OBJECT_CHALK);

	CThrow( const Point source, const Point destination, const int type, const int object = OBJECT_CHALK );

	~CThrow();

	bool setCThrowSource(  const int source_x, const int source_y );

	bool setCThrowDestination(  const int destination_x, const int destination_y );

	void finalizeCThrowInitiation();

	virtual bool drawIt();

private:

	Point source_;

	Point destination_;

	Point top_;

	int type_;

	float tStep_;

	float sStep_;

	bool ready_;

	std::string throwable_;

	boost::shared_ptr<CDynamicObject> object_; 

};

#endif

//~~CThrow.hpp
