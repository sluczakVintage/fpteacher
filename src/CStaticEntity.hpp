/**
* @author Sebastian Luczak
* @date 2009.01.04
* @version 0.1_draft
* 
* @brief klasa CStaticEntity jest klasa elementow statycznych, ktore mozna wyswietlac
*	
*/
#ifndef CSTATICENTITY_H
#define CSTATICENTITY_H

#include <string>
//#include "CSprite.hpp"
#include "CEntity.hpp"
#include "CWorld.hpp"
#include "CSpriteMgr.hpp"

using namespace std;
 
class CSprite;

class CStaticEntity : public CEntity
{
public:

	///konstruktor 
	///@param trzy liczby float
	CStaticEntity(float x, float y,	float z, const string& filename);
	///destruktor
	virtual ~CStaticEntity();
	///wyrysowanie (spite'a) do bufora
	virtual void draw();
	///wysokosci (spite'a)
	float getHeight() const;
	///szerokosc (spite'a)
	float getWidth() const;


protected:
	///wskaznik shared_ptr na CSprite odpowiadajacy danej CEntity
	//boost::shared_ptr<CSprite> sprite_;
	HCSprite spriteHandle_;

};


#endif
