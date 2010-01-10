/**
* @author Sebastian Luczak
* @date 2009.01.04
* @version 0.1_draft
* 
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
//#include "CAnimationMgr.hpp"

using namespace std;
 
class CDynamicEntity : public CEntity
{
public:

	///konstruktor 
	///@param trzy liczby float
	CDynamicEntity(float x, float y, float z, const string& filename);
	///destruktor
	virtual ~CDynamicEntity();
	///wyrysowanie (sprite'a z animacji) do bufora
	virtual void draw();


protected:
	///instancja animatora
	CAnimator animator_;
};


#endif

//~~CDynamicEntity.hpp
