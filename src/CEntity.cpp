#include "CEntity.hpp"

using namespace std;

CEntity::CEntity(float x, float y,	float z, string sprite)
{
	x_=x;
	y_=y;
	z_=z; 
}

CEntity::~CEntity(void)
{
	/* ~sprite_*/
}

void CEntity::draw()
{

}


float CEntity::getX()
{
	return x_;
}
float CEntity::getY()
{
	return y_;
}
float CEntity::getZ()
{
	return z_;
}