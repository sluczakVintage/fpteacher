/** @file CField.cpp
* @author Czarek Zawadka
* @date 2009.12.06
* @version 0.6
* 
* @brief klasa CField przedstawiajaca miejsce na sali
*
*/

#include "CAuditorium.hpp"

//prosty licznik sluzacy do zmiany kwestii wypowiadanej przez studenta
int CField::counter_ = 0;

//Konstruktor inicjalizujacy wszystkie parametry
CField::CField(float x,float y,float z, float w, float h, int row,int column)
	: x_(x),y_(y),z_(z),width_(w),height_ (h),isFree_(true),isBusy_(false),id_(row,column), entPtr_()
{
	CInput::getInstance()->addMouseObserver(*this);
	cout<<entPtr_.get()<<endl;
//	CEntity * ce =NULL;
//	entPtr_ = EntityPtr(ce);
}

//Konstruktor domyslny
CField::CField()
	: entPtr_()
{
//	CEntity * ce =NULL;
//	entPtr_ = EntityPtr(ce);
}

//Destruktor
CField::~CField()
{

}

//metoda zwraca true gdy argumenty sa wewnatrz prostokata pola
bool CField::isMouseOver(int mouseX, int mouseY)
{
	if(mouseX > x_ && mouseX < x_+ width_ &&  mouseY > y_ && mouseY < y_+ height_)
		return true;
	else 
		return false;
}

//czy pole jest zajete przez studenta
bool CField::getIsFree()
{
	return isFree_;
}

//@return czy student jest zajety przez jakas animacje etc.
bool CField::getIsBusy()
{
	return isBusy_;
}

//wspolrzedna X pola - liczone od lewej
float CField::getX()
{
	return x_;
}

//wspolrzedna Y pola - liczone od gory
float CField::getY()
{
 	return y_;
}

//wartosc bufora glebokosci
float CField::getZ()
{
 	return z_;
}

//szerokosc pola
float CField::getWidth()
{
	return width_;
}

//wysokosc pola
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

//metoda wywolywana przez klase CInput gdy zajdzie jakies zdarzenie od myszki
void CField::refresh(CMouseEvent * CMO)
{
	if (CMO->pressedX_ > x_ && CMO->pressedX_ < x_+ width_ &&  CMO->pressedY_ > y_ 
			&& CMO->pressedY_ < y_+ height_ && CMO->releasedX_ > x_ && CMO->releasedX_ < x_+ width_ 
				&&  CMO->releasedY_ > y_ && CMO->releasedY_ < y_+ height_)
	{
		if(!isFree_)
		{
			//CAudioSystem::getInstance()->set_sound_position("ziomek", getPosition() );
			cout << "trafiles ludka!, a jego pozycja x to " << getX() << ", natomiast y to " << getY() << " a pozycja do dzwieku to " << getPosition() << endl;
			string sound;
			if((entPtr_->getFilename() == "../res/graphics/sprites/students/rear/boy2.png") || (entPtr_->getFilename() == "../res/graphics/animsequences/2idle_sequence.dat"))
			{
				if(counter_%2)sound = "ziomek1";
				else sound = "ziomek2";
				//cout << " nazwa " << entPtr_->getFilename() << endl;
			}
			else if ((entPtr_->getFilename() == "../res/graphics/sprites/students/rear/boy1.png") || (entPtr_->getFilename() ==  "../res/graphics/animsequences/1idle_sequence.dat"))
			{
				if(counter_%2)sound = "normalny1";
				else sound = "normalny2";
				//cout << " nazwa " << entPtr_->getFilename() << endl;
			}
			else if ((entPtr_->getFilename() == "../res/graphics/sprites/students/rear/boy3.png") || (entPtr_->getFilename() ==  "../res/graphics/animsequences/3idle_sequence.dat"))
			{
				if(counter_%2)sound = "kujon1";
				else sound = "kujon2";
				//cout << " nazwa " << entPtr_->getFilename() << endl;
			}
			else cout << "zle dzwieki" << endl;
			cout << " nazwa " << entPtr_->getFilename() << endl;
				CAudioSystem::getInstance()->set_sound_position(sound, getPosition() , getDistance() );
				CAudioSystem::getInstance()->play_sound(sound);
				counter_++;
				//wyslanie przez siec:
				CSoundNetworkEvent * cne =  new CSoundNetworkEvent (getPosition(),getDistance(), sound);
				cne->send();
		}
		else
		{
			int type =  (CTimer::getInstance()->getTime())%9;
			CStudentNetworkEvent * cStudNE = new CStudentNetworkEvent(id_.first,id_.second,type);
			CAuditorium::getInstance()->seatNewStudent(id_.first,id_.second,type);	
			cStudNE->send();
		}   
	}

}

//pozycja czlowieka, potrzeba do odtwarzania dzwieku 3d
int CField::getPosition()
{
	float x=getX() + 32;
	//if (x==0) x=1;
	x = (x*180)/1024;
	int newX = static_cast<int>(x);
	newX=(newX+270)%360;
	return newX;

}

//dleglosc czlowieka, potrzebna do odtwarzania dzwieku 3d
int CField::getDistance()
{
	float y=getY() + 32;
	//if (x==0) x=1;
	y/=3;
	y-=255;
	y/=-1;
	int newY = static_cast<int>(y);
	return newY;
}

//~~CField.cpp
