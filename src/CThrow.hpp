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

#include "utils.hpp"
#include "CSpriteMgr.hpp"

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

class CThrow
{
public:

	CThrow();

	~CThrow();

	CThrow( const Point source, const Point destination, const int object = OBJECT_CHALK, const int trajectory = TRAJECT_PARABOLA );

	void setCThrowType( const int object = OBJECT_CHALK, const int trajectory = TRAJECT_PARABOLA );

	void CThrow::setCThrowSource(  const int source_x, const int source_y, const int source_z = 0 );

	void setCThrowSource( const float source_x, const float source_y, const float source_z = 0.f );

	void setCThrowDestination( const float destination_x, const float destination_y, const float destination_z = 0.f );

	void throwNow( const int minigame_result ) const;

private:
	Point source_;

	Point destination_;

	int object_;

	int trajectory_;

	HCSprite chalk_;

	HCSprite paperball_;

	//HCSprite cloth_;
};

#endif

//~~CThrow.hpp
