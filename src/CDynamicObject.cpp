/** @file CDynamicObject.cpp
* @author Sebastian Luczak
* @date 2010.02.24
* @version 0.6
 
* @brief klasa CDynamicObject jest klasa elementow posiadajacych animacje, mozliwych do wyswietlenia na ekranie, nie bedacych encja
*	
*/


#include "CDynamicObject.hpp"

using namespace std;


//konstruktor 
//@param trzy liczby float
CDynamicObject::CDynamicObject(float x, float y, float z, const string& filename, int position, int distance): x_(x), y_(y), z_(z)
{
	animator_.setAudioParam(position, distance);
	animator_.openFile(filename, 1);
	animator_.playAnimation();
	
	cout<<"CDynamicObject::CDynamicObject: tworzenie zakoñczone sukcesem"<<endl;
}

CDynamicObject::~CDynamicObject()
{
	cout<<"CDynamicObject::~CDynamicObject: niszczenie"<<endl;
}

//woluje metode rysowania
bool CDynamicObject::drawIt()
{
	animator_.animate(x_,y_);

	return true;
}

void CDynamicObject::updatePosition(const float x, const float y, const float z)
{	
	x_ = x;
	y_ = y;
	if( z != 905382.f)
		z_ = z;
}

//~~CDynamicObject.cpp
