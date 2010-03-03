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

//naglowki OpenGL
#if defined(_WIN32) 
#include <windows.h> 
#endif
#include <GL/gl.h>	
#include <GL/glu.h>	

#include <string>

#include <boost/smart_ptr.hpp>

#include "utils.hpp"
//#include "CSpriteMgr.hpp"

#include "CThrow.hpp"
#include "CVideoSystem.hpp"
#include "CDynamicObject.hpp"
#include "CVideoOverlay.hpp"

using namespace utils;

enum 
{
	TRAJECT_PARABOLA,
	TRAJECT_LINE,
	TRAJECT_RANDOM

};

enum
{
	OBJECT_CHALK,
	OBJECT_PAPERBALL/*,
	OBJECT_PLANE,
	OBJECT_CLOTH
	*/
};

class CThrow : public CVideoOverlay
{
public:

	CThrow( const int object = OBJECT_CHALK, const int trajectory = TRAJECT_PARABOLA );

	~CThrow();

	CThrow( const Point source, const Point destination, const int object = OBJECT_CHALK, const int trajectory = TRAJECT_PARABOLA );

	void setCThrowSource(  const int source_x, const int source_y, const int source_z = 0 );

	void setCThrowSource( const float source_x, const float source_y, const float source_z = 0.f );

	void setCThrowDestination( const float destination_x, const float destination_y, const float destination_z = 0.f );

	void setCThrowDestination(  const int destination_x, const int destination_y, const int destination_z = 0 );

	void finalizeCThrowInitiation();

	virtual bool drawIt();

private:

	Point source_;

	Point destination_;

	Point top_;

	int trajectory_;

	float tStep_;

	float sStep_;

	bool ready_;

	std::string throwable_;

	boost::shared_ptr<CDynamicObject> object_; 

};

#endif

//~~CThrow.hpp
