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

	CThrow( Point source, Point destination, int object = OBJECT_CHALK, int trajectory = TRAJECT_PARABOLA );

	setCThrow( Point source, Point destination, int object = OBJECT_CHALK, int trajectory = TRAJECT_PARABOLA);

	throwNow();

private:
	Point source_;
	Point destination_;

	int object;

	int trajectory_;

};

#endif

//~~CThrow.hpp
