/** @file CStaticEntity.cpp
* @author Czarek Zawadka
* @date 2009.12.06
* @version 0.4
* 
* @brief klasa CStatiCStaticEntity jest klasa elementow statycznych, ktore mozna wyswietlic na ekranie
*
*/


#include "CStaticEntity.hpp"

using namespace std;


//konstruktor 
CStaticEntity::CStaticEntity(float x, float y,	float z, const string& filename)
	: CEntity(x,y,z,filename)
{
	type_ = "CStaticEntity";
	spriteHandle_= CSpriteMgr::getInstance()->getCSprite(filename);
	///Encja sama dodaje sie do CWorld
	CWorld::getInstance()-> addEntity(*this);
	cout<<"CStaticEntity::CStaticEntity: tworzenie zakoñczone sukcesem"<<endl;
}

CStaticEntity::~CStaticEntity(void)
{
	cout<<"CStaticEntity::~CStaticEntity: nieszczenie"<<endl;
}

//woluje metode rysowania w CSprite, patrz todo
void CStaticEntity::draw()
{
	CVideoSystem::getInstance()->drawCSprite(x_,y_,CSpriteMgr::getInstance()->getCSpritePtr(spriteHandle_));
}

//@return wysokosc grafiki z CSprite nalezacego do danego CStaticEntity
float CStaticEntity::getHeight() const
{
	return CSpriteMgr::getInstance()->getCSpritePtr(spriteHandle_)->getSpriteHeight();
}
//@return szerokosc grafiki z CSprite nalezacego do danego CStaticEntity
float CStaticEntity::getWidth() const
{
	return CSpriteMgr::getInstance()->getCSpritePtr(spriteHandle_)->getSpriteWidth();
}


//~~CStaticEntity.cpp
