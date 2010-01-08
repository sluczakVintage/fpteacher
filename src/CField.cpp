/** @file CField.cpp
* @author Czarek Zawadka
* @date 2009.12.06
* @version 0.1_draft
* 
* @brief klasa CField przedstawiajaca miejsce na sali
*
*
* Klasa opisuje jedno miejsce na sali, które mo¿e byæ zajête przez studenta. Zawiera podstawowe informacje o miejscu - 
* wspolrzedne, oraz to, czy miejsce jest zajete. Klasa moze zostac zserializowana przez archiwa z boost::serializable.
*
*@todo zastanowic sie kto powienien wiedziec ze encja na danym miejscu jest czyms zajeta
*@todo zastanowic sie czy szablon do serializacji nie powinien byc prywarny a klasa boost::serialization::access zaprzyjazniona
*/

#include "CField.hpp"

CField::CField(float x,float y,float z, float w, float h, int row,int column)
	: x_(x),y_(y),z_(z),width_(w),height_ (h),isFree_(true),isBusy_(false),id_(row,column), entPtr_()
{
	CInput::getInstance()->addMouseObserver(*this);
	cout<<entPtr_.get()<<endl;
//	CEntity * ce =NULL;
//	entPtr_ = EntityPtr(ce);
}

CField::CField()
	: entPtr_()
{
//	CEntity * ce =NULL;
//	entPtr_ = EntityPtr(ce);
}

CField::~CField()
{

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

void CField::refresh()
{
	//cout << "elo elo" << endl;
}