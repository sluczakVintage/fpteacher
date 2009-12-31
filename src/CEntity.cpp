/** @file CEntity.cpp
* @author Czarek Zawadka
* @date 2009.12.06
* @version 0.1_draft
* 
* @brief klasa CEntity jest blas¹ bazow¹ dla elementów, które mozna wyœwietliæ na ekranie
*
* @todo przemysle zarzadzanie CEntity -  kto powinien wywolywac konstruktory, 
*	kto powinien dodawac i usuwac CEntity ze swiata gry 	
*/


#include "CEntity.hpp"

using namespace std;

/*
CEntity::CEntity()
{	
}
*/

///konstruktor 
///@param trzy liczby float
CEntity::CEntity(float x, float y,	float z, const string& filename)
{
	x_=x;
	y_=y;
	z_=z;
	
	//if(&filename != NULL)
	sprite_ = boost::shared_ptr<CSprite>(new CSprite(filename));
	
	///Encja sama dodaje sie do CWorld
	CWorld::getInstance()-> addEntity(*this);
	cout<<"CEntity::CEntity: tworzenie zakoñczone sukcesem"<<endl;
}

CEntity::~CEntity(void)
{
//	CWorld::getInstance()-> removeEntity(*this);
	cout<<"CEntity::~CEntity: nieszczenie"<<endl;
}

///woluje metode rysowania w CSprite, patrz todo
void CEntity::draw()
{
	CVideoSystem::getInstance()->drawCSprite(x_,y_,*sprite_);
}

float CEntity::getX() const
{
	return x_;
}

float CEntity::getY() const
{
	return y_;
}

float CEntity::getZ() const
{
	return z_;
}

///@return wysokosc grafiki z CSprite nalezacego do danego CEntity
float CEntity::getHeight() const
{
	return sprite_->getSpriteHeight();
}
///@return szerokosc grafiki z CSprite nalezacego do danego CEntity
float CEntity::getWidth() const
{
	return sprite_->getSpriteWidth();
}

///@return true gdy e1.z_<e2.z_ lub e1 blizej punktu (0,0) na ekranie (lewego gornego rogu)
bool operator<(const CEntity& e1 ,const CEntity& e2 )
{

	float e1Z = e1.getZ();
	float e2Z = e2.getZ();

	if( e1Z < e2Z)
		return true;
	else
		if( e1Z> e2Z)
			return false;
		else
		{
			float e1X = e1.getX();
			float e1Y = e1.getY();
			float e2X = e2.getX();
			float e2Y = e2.getY();
			return (( e1X)*( e1X) +( e1Y)*( e1Y) < ( e2X)*( e2X) +( e2Y)*( e2Y)) ? true : false;
		}
}
