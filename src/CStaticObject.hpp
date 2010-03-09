/**\file
* @author Sebastian Luczak
* @date 2010.02.24
* @version 0.1
* @class CStaticObject CStaticObject.hpp
* @brief klasa CStaticObject jest klasa elementow mozliwych do wyswietlenia na ekranie, nie bedacych encjami
*	
*/

#ifndef CSTATICOBJECT_H
#define CSTATICOBJECT_H

#include <string>
#include <list>

#include "CSpriteMgr.hpp"
#include "CVideoSystem.hpp"
#include "CVideoOverlay.hpp"
#include "CLog.hpp"

using namespace std;

class CStaticObject : public CVideoOverlay
{
public:

	///konstruktor 
	///@param filename sciezka do ladowanego pliku
	///@param x wspolzedna x
	///@param y wspolzedna y
	///@param z wspolzedna z
	CStaticObject(float x, float y, float z, const string& filename, int position = 0, int distance = 0);

	///destruktor
	~CStaticObject();

	///wyrysowanie (sprite'a z animacji) do bufora
	virtual bool drawIt();

	void updatePosition(const float x, const float y, const float z = 905382.f);

protected:
	///instancja animatora
	HCSprite spriteHandle_;

	///wspolrzedna x'owa - os X przebiega z lewej do prawej
	float x_;

	///wspolrzedna y'owa - os Y przebiega z gory na dol
	float y_;

	///pseudo-wspolrzedna oznaczajaca bufor Z
	float z_;

};


#endif

//~~CStaticObject.hpp
