/**\file
* @author Sebastian Luczak
* @date 2009.01.04
* @version 0.6
* @class CDynamicEntity CDynamicEntity.hpp
* @brief klasa CDynamicEntity jest klasa elementow posiadajacych animacje, mozliwych do wyswietlenia na ekranie
*	
*/
#ifndef CDYNAMICENTITY_H
#define CDYNAMICENTITY_H

#include <string>
#include <list>

#include "CEntity.hpp"
#include "CWorld.hpp"
#include "CAnimator.hpp"
#include "CAuditorium.hpp"

using namespace std;

///definicja typu boost::shared_ptr<CFieldPtr>;
class CDynamicEntity : public CEntity
{
public:

	///konstruktor 
	///@param filename sciezka do ladowanego pliku
	///@param x wspolzedna x
	///@param y wspolzedna y
	///@param z wspolzedna z
	CDynamicEntity(float x, float y, float z, const string& filename, int position = 0, int distance = 0);

	///destruktor
	virtual ~CDynamicEntity();

	///wyrysowanie (sprite'a z animacji) do bufora
	virtual void draw();

	void updatePosition(const float x, const float y, const float z = 905382.f);

protected:
	///instancja animatora
	CAnimator animator_;

};


#endif

//~~CDynamicEntity.hpp
