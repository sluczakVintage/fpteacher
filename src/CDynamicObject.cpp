/** @file CDynamicObject.cpp
* @author Sebastian Luczak
* @date 2010.02.24
* @version 0.6
 
* @brief klasa CDynamicObject jest klasa elementow posiadajacych animacje, mozliwych do wyswietlenia na ekranie, nie bedacych encja
*	
*/


#include "CDynamicObject.hpp"

int CDynamicObject::counter_ = 0;

using namespace std;


//konstruktor 
//@param trzy liczby float
CDynamicObject::CDynamicObject(float x, float y, float z, const string& filename, int position, int distance): x_(x), y_(y), z_(z)
{
	uid_ = counter_;
	counter_++;
	animator_.setAudioParam(position, distance);
	animator_.openFile(filename, true);
	animator_.playAnimation();
	
	CWorld::getInstance()-> addObject(*this);

	cout<<"CDynamicObject::CDynamicObject: tworzenie zakoñczone sukcesem"<<endl;
}

CDynamicObject::~CDynamicObject()
{
	cout<<"CDynamicObject::~CDynamicObject: niszczenie"<<endl;
}

//woluje metode rysowania
void CDynamicObject::draw()
{
	animator_.animate(x_,y_);
}

int CDynamicObject::getUID() const
{
	return uid_;
}

void CDynamicObject::updatePosition(const float x, const float y, const float z)
{	
	x_ = x;
	y_ = y;
	if( z != 905382.f)
		z_ = z;
}

//~~CDynamicObject.cpp
