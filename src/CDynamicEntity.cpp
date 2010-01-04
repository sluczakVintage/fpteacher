/** @file CEntity.cpp
* @author Sebastian Luczak
* @date 2009.01.04
* @version 0.1_draft
 
* @brief klasa CDynamicEntity jest klasa elementów posiadajacych animacje, mozliwych do wyswietlenia na ekranie
*	
*/


#include "CDynamicEntity.hpp"

using namespace std;


///konstruktor 
///@param trzy liczby float
CDynamicEntity::CDynamicEntity(float x, float y, float z, const string& filename)
{
	x_=x;
	y_=y;
	z_=z;
	
	//if(&filename != NULL)
	animation_ = boost::shared_ptr<CAnimation>(new CAnimation(filename));
	
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

///woluje metode rysowania w CSprite, patrz todo
void CDynamicEntity::draw()
{
	CVideoSystem::getInstance()->animateCAnimation(x_,y_,*animation_);
}



//~~CDynamicEntity.cpp
