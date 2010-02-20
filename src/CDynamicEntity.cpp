/** @file CEntity.cpp
* @author Sebastian Luczak
* @date 2009.01.04
* @version 0.6
 
* @brief klasa CDynamicEntity jest klasa elementow posiadajacych animacje, mozliwych do wyswietlenia na ekranie
*	
*/


#include "CDynamicEntity.hpp"

using namespace std;


//konstruktor 
//@param trzy liczby float
CDynamicEntity::CDynamicEntity(float x, float y, float z, const string& filename, int position, int distance)
	: CEntity(x,y,z,filename)
{
	type_ = "CDynamicEntity";
	animator_.setAudioParam(position, distance);
	animator_.openFile(filename);
	animator_.playAnimation();

	cout << "ANIMACJA STWORZONA!!" << endl;
	///Encja sama dodaje sie do CWorld
	CWorld::getInstance()-> addEntity(*this);

	cout<<"CDynamicEntity::CDynamicEntity: tworzenie zakoñczone sukcesem"<<endl;
}

CDynamicEntity::~CDynamicEntity(void)
{
//	CWorld::getInstance()-> removeEntity(*this);
	cout<<"CDynamicEntity::~CDynamicEntity: niszczenie"<<endl;
}

//woluje metode rysowania
void CDynamicEntity::draw()
{
	animator_.animate(x_,y_);
}


//~~CDynamicEntity.cpp
