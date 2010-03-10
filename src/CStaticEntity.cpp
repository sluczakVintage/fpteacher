/** @file CStaticEntity.cpp
* @author Czarek Zawadka
* @date 2009.12.06
* @version 0.6
* 
* @brief klasa CStatiCStaticEntity jest klasa elementow statycznych, ktore mozna wyswietlic na ekranie
*
*/


#include "CStaticEntity.hpp"

using namespace std;
using namespace logging;


//konstruktor 
CStaticEntity::CStaticEntity(float x, float y,	float z, const string& filename)
	: CEntity(x,y,z,filename)
{
	type_ = "CStaticEntity";
	spriteHandle_= CSpriteMgr::getInstance()->getCSprite(filename);
	///Encja sama dodaje sie do CWorld
	CWorld::getInstance()-> addEntity(*this);
	CLog::getInstance()->sss << "CStaticEntity::CStaticEntity: tworzenie zakonczone sukcesem"<<endl;
	logs(CLog::getInstance()->sss.str(), INFO);
}

CStaticEntity::~CStaticEntity(void)
{
	CLog::getInstance()->sss << "CStaticEntity::~CStaticEntity: nieszczenie"<<endl;
	logs(CLog::getInstance()->sss.str(), INFO);
	
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
