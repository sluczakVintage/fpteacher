#include "CField.hpp"

CField::CField(float x,float y,float z, float w, float h, int row,int column)
{
	x_=x;
	y_=y;
	z_=z;
	id_.first = row;
	id_.second = column;
	width_ = w; 
	height_ = h; 
}

CField::~CField()
{
	//std::cout<<"CField::~CField()"<<endl;
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
	return isFree_;
}

bool CField::getIsBusy()
{
	return isBusy_;
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
float CField::getWidth()
{
	return width_;
}
float CField::getHeight()
{
	return height_;
}