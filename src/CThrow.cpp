/** @file CThrow.cpp
* @author Sebastian luczak
* @date 2010.02.23
* @version 0.1
* @brief 
*  
*		
*/
#include "CThrow.hpp"

int CVideoOverlay::counter_ = 0;

CThrow::CThrow( const int object,  const int trajectory ) : trajectory_(trajectory)
{
	switch (object)
	{
		case OBJECT_CHALK:
			throwable_ = PATH_ANIM_SEQUENCES+"chalk_throw.dat";
			break;
		case OBJECT_PAPERBALL:
			throwable_ = PATH_ANIM_SEQUENCES+"paperball_throw.dat";
			break;
		default:
			break;
	}
	object_ = boost::shared_ptr<CDynamicObject>(new CDynamicObject(0.f, 0.f, 100.f, throwable_, 0, 0));
	source_ = utils::Point(0.f, 0.f, 0.f);
	destination_ = utils::Point(0.f, 0.f, 0.f);

	selfPtr_ = boost::shared_ptr<CVideoOverlay>(this);	
}

CThrow::~CThrow()
{
	cout << "DESTRUKCJA CThrow" << endl;
}

CThrow::CThrow( const Point source, const Point destination, const int object,  const int trajectory ) : trajectory_(trajectory)
{
	switch (object)
	{
		case OBJECT_CHALK:
			throwable_ = PATH_ANIM_SEQUENCES+"chalk_throw.dat";
			break;
		case OBJECT_PAPERBALL:
			throwable_ = PATH_ANIM_SEQUENCES+"paperball_throw.dat";
			break;
		default:
			break;
	}
	source_ = source;
	destination_ = destination;
	object_ = boost::shared_ptr<CDynamicObject>(new CDynamicObject(0.f, 0.f, 100.f, throwable_, 0, 0));

	selfPtr_ = boost::shared_ptr<CVideoOverlay>(this);	

	CWorld::getInstance()->addOverlay(selfPtr_);
}

void CThrow::setCThrowSource(  const int source_x, const int source_y, const int source_z )
{
	setCThrowSource(static_cast<float>(source_x), static_cast<float>(source_y), static_cast<float>(source_z));
}


void CThrow::setCThrowSource(  const float source_x, const float source_y, const float source_z )
{
	source_ = Point(source_x, source_y, source_z); 
}

void CThrow::setCThrowDestination( const int destination_x, const int destination_y, const int destination_z )
{
	setCThrowDestination(static_cast<float>(destination_x), static_cast<float>(destination_y), static_cast<float>(destination_z));
}

void CThrow::setCThrowDestination( const float destination_x, const float destination_y, const float destination_z )
{
	destination_ = Point(destination_x, destination_y, destination_z); 
	
	CWorld::getInstance()->addOverlay(selfPtr_);
}

bool CThrow::drawIt()
{
	Vector2f v1 = Vector2f(source_, destination_);
	Vector2f v2, v3, v4;

	Point top;
	float x, y;
	static float t = 0.f;

	switch(trajectory_)
	{
	
	case TRAJECT_PARABOLA:

			v2 = multiplyVector2f(v1, 0.5f);		
			v3 = getOrthogonalVector2f(v2);
			v4 = multiplyVector2f(v3, 4.0f);
			
			top = getEndPoint(source_, addVectors2f(v2, v4));
			
			// Obliczanie krzywej Bezier'a
			// do implementacji wraz z animacj¹
			if( t <= 1.f )
			{	
				x = (1 - t)*(1 - t)*source_.x_ + 2*(1 - t)*t*top.x_ + t*t*destination_.x_;
				y = (1 - t)*(1 - t)*source_.y_ + 2*(1 - t)*t*top.y_ + t*t*destination_.y_;
				object_->updatePosition(x, y);
				CVideoSystem::getInstance()->setScale(1.2f-t);
				object_->draw();
				t = t + 0.05f; // uwzglednic odleglosc od celu
				return false;
			}
			else
			{
				t = 0.f;
				return true;
			}
			
		break;

	case TRAJECT_LINE:
		return true;
		break;
	case TRAJECT_RANDOM:
		return true;
		break;
	default:
		return false;
		break;

	}
}


int CThrow::getUID() const
{
	return uid_;
}

//~~CThrow.cpp