/** @file CThrow.cpp
* @author Sebastian luczak
* @date 2010.02.23
* @version 0.1
* @brief 
*  
*		
*/
#include "CThrow.hpp"

CThrow::CThrow() : object_(OBJECT_CHALK), trajectory_(TRAJECT_PARABOLA)
{
	chalk_ = CSpriteMgr::getInstance()->getCSprite(PATH_SPRITES_MINIGAMES+"throw/throw_chulk.png");
	//paperball_ = CSpriteMgr::getInstance()->getCSprite(PATH_SPRITES_MINIGAMES+"throw/throw_paperBall.png");
	source_ = utils::Point(0.f, 0.f, 0.f);
	destination_ = utils::Point(0.f, 0.f, 0.f);
}


CThrow::~CThrow()
{


}

CThrow::CThrow( const Point source, const Point destination, const int object, const int trajectory ) : object_(OBJECT_CHALK), trajectory_(TRAJECT_PARABOLA)
{
	source_ = source;
	destination_ = destination;
}

void CThrow::setCThrowSource(  const int source_x, const int source_y, const int source_z )
{
	setCThrowSource(static_cast<float>(source_x), static_cast<float>(source_y), static_cast<float>(source_z));
}


void CThrow::setCThrowSource(  const float source_x, const float source_y, const float source_z )
{
	source_ = Point(source_x, source_y, source_z); 
}

void CThrow::setCThrowDestination( const float destination_x, const float destination_y, const float destination_z )
{
	destination_ = Point(destination_x, destination_y, destination_z); 
}

void CThrow::setCThrowType( const int object, const int trajectory )
{
	object_ = object;
	trajectory_ = trajectory;
}

void CThrow::throwNow( const int minigame_result) const
{
	float distance;
	Vector2f v1 = Vector2f(source_, destination_);
	Vector2f v2, v3;

	switch(trajectory_)
	{
	
	case TRAJECT_PARABOLA:
		distance = distanceBetween(source_, destination_);
		cout << distance << endl;

		v2 = multiplyVector2f(v1, 0.5);
		cout << v1.x_ << endl;
		cout << v1.y_ << endl;
		cout << v2.x_ << endl;
		cout << v2.y_ << endl;
		
		v3 = getOrthogonalVector2f(v2);
		cout << v2.x_ << endl;
		cout << v2.y_ << endl << endl;
		cout << v3.x_ << endl;
		cout << v3.y_ << endl;
		

		break;

	case TRAJECT_LINE:

		break;
	case TRAJECT_RANDOM:

		break;
	default:
		break;

	}
}

//~~CThrow.cpp