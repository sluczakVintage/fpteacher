/** @file CStatiCStaticEntity.cpp
* @author Czarek Zawadka
* @date 2009.12.06
* @version 0.1_draft
* 
* @brief klasa CStatiCStaticEntity jest klas¹ elementow statycznych, ktore mozna wyœwietliæ na ekranie
*
*/


#include "CStaticEntity.hpp"

using namespace std;


///konstruktor 
///@param trzy liczby float
CStaticEntity::CStaticEntity(float x, float y,	float z, const string& filename)
	: CEntity(x,y,z,filename)
{
	type_ = "CStaticEntity";
	//if(&filename != NULL)
	//sprite_ = boost::shared_ptr<CSprite>(new CSprite(filename));
	spriteHandle_= CSpriteMgr::getInstance()->getCSprite(filename);
	///Encja sama dodaje sie do CWorld
	CWorld::getInstance()-> addEntity(*this);
	cout<<"CStaticEntity::CStaticEntity: tworzenie zakoñczone sukcesem"<<endl;
}

CStaticEntity::~CStaticEntity(void)
{
//	CWorld::getInstance()-> removeEntity(*this);
	cout<<"CStaticEntity::~CStaticEntity: nieszczenie"<<endl;
}

///woluje metode rysowania w CSprite, patrz todo
void CStaticEntity::draw()
{
	CVideoSystem::getInstance()->drawCSprite(x_,y_,CSpriteMgr::getInstance()->getCSpriteInstance(spriteHandle_));
}

///@return wysokosc grafiki z CSprite nalezacego do danego CStaticEntity
float CStaticEntity::getHeight() const
{
	return CSpriteMgr::getInstance()->getCSpriteInstance(spriteHandle_)->getSpriteHeight();
}
///@return szerokosc grafiki z CSprite nalezacego do danego CStaticEntity
float CStaticEntity::getWidth() const
{
	return CSpriteMgr::getInstance()->getCSpriteInstance(spriteHandle_)->getSpriteWidth();
}

