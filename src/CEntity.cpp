#include "CEntity.hpp"

using namespace std;

/*
CEntity::CEntity()
{	
}
*/
CEntity::CEntity(float x, float y,	float z, const string& filename)
{
	x_=x;
	y_=y;
	z_=z;
	//cout<<"CEntity::CEntity:"<<endl;
	
	if(&filename != NULL)
		sprite_ = boost::shared_ptr<CSprite>(new CSprite(filename));
		
	CWorld::getInstance()-> addEntity(*this);

}

CEntity::~CEntity(void)
{
//	CWorld::getInstance()-> removeEntity(*this);
	cout<<"CEntity::~CEntity"<<endl;
}

void CEntity::draw()
{
	sprite_ -> drawCSprite(x_,y_);
}

float CEntity::getX() const
{
	return x_;
}

float CEntity::getY() const
{
	return y_;
}

float CEntity::getZ() const
{
	return z_;
}

float CEntity::getHeight() const
{
	return sprite_->getSpriteHeight();
}

float CEntity::getWidth() const
{
	return sprite_->getSpriteWidth();
}

bool operator<(const CEntity& e1 ,const CEntity& e2 )
{

	float e1Z = e1.getZ();
	float e2Z = e2.getZ();

	if( e1Z < e2Z)
		return true;
	else
		if( e1Z> e2Z)
			return false;
		else
		{
			float e1X = e1.getX();
			float e1Y = e1.getY();
			float e2X = e2.getX();
			float e2Y = e2.getY();
			return (( e1X)*( e1X) +( e1Y)*( e1Y) < ( e2X)*( e2X) +( e2Y)*( e2Y)) ? true : false;
		}
}
