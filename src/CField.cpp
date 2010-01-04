#include "CField.hpp"

CField::CField(float x,float y,float z,int row,int column,float h,float w)
{
	x_=x;
	y_=y;
	z_=z;
	id_.first = row;
	id_.second = column;
}

bool CField::isMouseOver(int mouseX, int mouseY)
{
	if(mouseX > x_ && mouseX < x_+ width_ &&  mouseY > y_ && mouseY < y_+ height_)
		return true;
	else 
		return false;
}

bool CField::getIsFree()
{
	return isFree;
}

bool CField::getIsBusy()
{
	return isBusy;
}
	
float CField::getX()
{
	return x_;
}

float CField::getY()
{
 	return y_;
}

float CField::getZ()
{
 	return z_;
}