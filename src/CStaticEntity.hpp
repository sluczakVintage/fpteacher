/**
* @author Czarek Zawadka
* @date 2009.12.06
* @version 0.1_draft
* @brief klasa CStaticEntity jest blas¹ bazow¹ dla elementów otoczenia, które nie mog¹ siê poruszaæ ani animowaæ
*	
*	
*/
#ifndef STATIC_ENTITY_H
#define STATIC_ENTITY_H
//#include "CEntity.hpp"
//#include "globals.hpp"



#include <iostream>
#include <string>
#include "CEntity.hpp"
using namespace std;

class CEntity;

class CStaticEntity: public CEntity
{
public:
	CStaticEntity(float x, float y,	float z, const string& filename  = NULL);
	
//	virtual ~CStaticEntity();
//	virtual void draw();

	
};

#endif