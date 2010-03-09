/**\file
* @author Sebastian Luczak
* @date 2010.02.24
* @version 0.1
* @class CDynamicObject CDynamicObject.hpp
* @brief klasa CDynamicObject jest klasa elementow posiadajacych animacje, mozliwych do wyswietlenia na ekranie, nie bedacych encjami
*	
*/

#ifndef CDYNAMICOBJECT_H
#define CDYNAMICOBJECT_H

#include <string>
#include <list>

#include "CAnimator.hpp"
#include "CVideoOverlay.hpp"

#include "CLog.hpp"

using namespace std;

class CDynamicObject : public CVideoOverlay
{
public:

	///konstruktor 
	///@param filename sciezka do ladowanego pliku
	///@param x wspolzedna x
	///@param y wspolzedna y
	///@param z wspolzedna z
	CDynamicObject(float x, float y, float z, const string& filename, int position = 0, int distance = 0);

	///destruktor
	~CDynamicObject();

	///wyrysowanie (sprite'a z animacji) do bufora
	virtual bool drawIt();

	void updatePosition(const float x, const float y, const float z = 905382.f);

protected:
	///instancja animatora
	CAnimator animator_;

	///wspolrzedna x'owa - os X przebiega z lewej do prawej
	float x_;

	///wspolrzedna y'owa - os Y przebiega z gory na dol
	float y_;

	///pseudo-wspolrzedna oznaczajaca bufor Z
	float z_;

};


#endif

//~~CDynamicObject.hpp
