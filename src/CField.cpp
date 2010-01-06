#include "CField.hpp"

CField::CField(float x,float y,float z, float w, float h, int row,int column)
	: x_(x),y_(y),z_(z),width_(w),height_ (h),isFree_(true),isBusy_(false),id_(row,column)
{

}

CField::~CField()
{
	std::cout<<"~~!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!CField::~CField()"<<endl;
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

/*
export template<class Archive> 
	void CField::serialize(Archive &ar, const unsigned int version)
{
	
		ar & BOOST_SERIALIZATION_NVP(id_.first);
		ar & BOOST_SERIALIZATION_NVP(id_.second);
		ar & BOOST_SERIALIZATION_NVP(x_);
		ar & BOOST_SERIALIZATION_NVP(y_);
		ar & BOOST_SERIALIZATION_NVP(z_);
		ar & BOOST_SERIALIZATION_NVP( width_);
		ar & BOOST_SERIALIZATION_NVP(height_);
		ar & BOOST_SERIALIZATION_NVP(isFree_);
		ar & BOOST_SERIALIZATION_NVP(isBusy_);
}
*/