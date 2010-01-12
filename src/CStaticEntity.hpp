/**\file
* @author Sebastian Luczak
* @date 2009.01.04
* @version 0.6
* @class CStaticEntity CStaticEntity.hpp
* @brief klasa CStaticEntity jest klasa elementow statycznych, ktore mozna wyswietlac
*	
*/
#ifndef CSTATICENTITY_H
#define CSTATICENTITY_H

#include <string>
//naglowki klas aplikacji
#include "CEntity.hpp"
#include "CWorld.hpp"
#include "CVideoSystem.hpp"
#include "CSpriteMgr.hpp"

using namespace std;
 

class CStaticEntity : public CEntity
{
public:

	///konstruktor 
	///@param filename sciezka do ladowanego pliku
	///@param x wspolzedna x
	///@param y wspolzedna y
	///@param z wspolzedna z
	CStaticEntity(float x, float y,	float z, const string& filename);
	///destruktor
	virtual ~CStaticEntity();
	///wyrysowanie (spite'a) do bufora
	virtual void draw();
	///wysokosc (spite'a)
	float getHeight() const;
	///szerokosc (spite'a)
	float getWidth() const;


protected:
	///uchwyt do sprite'a
	HCSprite spriteHandle_;

};


#endif

//~~CStaticEntity.hpp
