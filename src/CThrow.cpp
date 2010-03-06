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

CThrow::CThrow( const int type, const int object ) : type_(type), tStep_(0.02f), sStep_(0.0f), scale_(1.0f), ready_(false)
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
	top_ = utils::Point(0.f, 0.f, 0.f);
	destination_ = utils::Point(0.f, 0.f, 0.f);

	selfPtr_ = boost::shared_ptr<CVideoOverlay>(this);	
}


CThrow::CThrow( const Point source, const Point destination, const int type, const int object ) : type_(type), tStep_(0.02f), sStep_(0.0f), scale_(1.0f), ready_(false)
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
	top_ = utils::Point(0.f, 0.f, 0.f);
	destination_ = destination;
	object_ = boost::shared_ptr<CDynamicObject>(new CDynamicObject(source.x_, source.y_, source.z_, throwable_, 0, 0));

	selfPtr_ = boost::shared_ptr<CVideoOverlay>(this);	
}

CThrow::~CThrow()
{
	cout << "DESTRUKCJA CThrow" << endl;
}


bool CThrow::setCThrowSource(const int source_x, const int source_y)
{
	float source_z;
	
	if(type_ == THROW_TEACHER)
		source_z = 200.f;
	else
	{
		CField* field = CAuditorium::getInstance()->getFieldPtr(static_cast<int>(source_x), static_cast<int>(source_y));
		// sprawdzam, czy kliknieto w pole
		if(field == NULL)
			//////@todo log
			return false;
		source_z = field->getZ();
		delete field;
	}

	source_ = Point(static_cast<float>(source_x), static_cast<float>(source_y), source_z); 
	return true;
}
//obsluzyc nietrafienie
bool CThrow::setCThrowDestination( const int destination_x, const int destination_y )
{
	float destination_z;
	CField* field = CAuditorium::getInstance()->getFieldPtr(static_cast<int>(destination_x), static_cast<int>(destination_y));
	// sprawdzam, czy kliknieto w pole
	if(field == NULL)
	{
		//////@todo log
		destination_ = Point(0.f, 0.f, 0.f);
		return false;
	}
	else
	{
		destination_z = field->getZ();
		destination_ = Point(static_cast<float>(destination_x), static_cast<float>(destination_y), static_cast<float>(destination_z));
		return true;
	}
	delete field;
}


void CThrow::finalizeCThrowInitiation()
{
	Vector2f v1 = Vector2f(source_, destination_);
	Vector2f v2, v3, v4;

	float absolute_distance;
			
	switch(type_)
	{
	
	case THROW_TEACHER:

			absolute_distance = fabsf(source_.z_ - destination_.z_);
			
			v2 = multiplyVector2f(v1, 0.5f);		
			v3 = getOrthogonalVector2f(v2);
			v4 = multiplyVector2f(v3, 4.0f);
			
			top_ = getEndPoint(source_, addVectors2f(v2, v4));

			top_.x_ = top_.x_ - (6.f - absolute_distance * 0.05f );
			top_.y_ = top_.y_ - ( absolute_distance * 0.3f );

			tStep_ = (source_.z_ - absolute_distance) * 0.001f;
			sStep_ = (absolute_distance * tStep_)/(source_.z_*0.01f) * 0.01f;

			///CLogic!!
			scale_ = 1.0f;
			cout << "a";
		break;

	case THROW_STUDENTS:
		break;
	default:
		break;

	}
	ready_ = true;
	CWorld::getInstance()->addOverlay(selfPtr_);
}

bool CThrow::drawIt()
{
	float x, y;
	static float t = 0.f;
	
	if(!ready_)
	{
		cout << "CThrow::drawIt(): Rzut nie w pe³ni zainicjalizowany" << endl;
		return false;
	}
	switch(type_)
	{
	
	case THROW_TEACHER:
			
			// Obliczanie krzywej Bezier'a
			// do implementacji wraz z animacj¹
			if( t <= 1.f )
			{	
				x = (1 - t)*(1 - t)*source_.x_ + 2*(1 - t)*t*top_.x_ + t*t*destination_.x_;
				y = (1 - t)*(1 - t)*source_.y_ + 2*(1 - t)*t*top_.y_ + t*t*destination_.y_;
				object_->updatePosition(x, y);
				CVideoSystem::getInstance()->setScale(scale_);
				object_->drawIt();
				t = t + tStep_; // uwzglednic odleglosc od celu
				scale_ = scale_ - sStep_;
				return false;
			}
			else
			{
				t = 0.f;
				ready_ = false;
				return true;
			}
			
		break;

	case THROW_STUDENTS:
		return true;
		break;
	default:
		return false;
		break;

	}
}


//~~CThrow.cpp