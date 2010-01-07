/**
* @author Sebastian Luczak
* @date 2009.01.04
* @version 0.1_draft
* 
* @brief klasa CDynamicEntity jest klasa elementów posiadajacych animacje, mozliwych do wyswietlenia na ekranie
*	
*/
#ifndef CDYNAMICENTITY_H
#define CDYNAMICENTITY_H

#include <string>
#include "CAnimation.hpp"
#include "CEntity.hpp"
#include "CWorld.hpp"
#include "CVideoSystem.hpp"

using namespace std;
 
class CAnimation;

class CDynamicEntity : public CEntity
{
public:

	///konstruktor 
	///@param trzy liczby float
	CDynamicEntity(float x, float y, float z, const string& filename);
	///destruktor
	virtual ~CDynamicEntity();
	///wyrysowanie (spite'a) do bufora
	virtual void draw();


protected:
	///wskaznik shared_ptr na CAnimation odpowiadajacy danej CDynamicEntity
	boost::shared_ptr<CAnimation> animation_;
};


#endif

//~~CDynamicEntity.hpp
