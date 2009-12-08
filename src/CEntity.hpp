/**
* @author Czarek Zawadka
* @date 2009.12.06
* @version 0.1_draft
* @brief klasa CEntity jest abstrakcyjna blas¹ bazow¹ dla elementów, które mozna wyœwietliæ na ekranie
*	
*	
*/
#ifndef ENTITY
#define ENTITY

#include <iostream>
#include <string>
#include <boost/shared_ptr.hpp>

using namespace std;
 

class CEntity
{
public:

	CEntity(float x, float y,	float z, string sprite  = NULL);
	virtual ~CEntity();
	virtual void draw();
	float getX();
	float getY();
	float getZ();
	float getHeight(){/*return sprite.getHeHeight*/};
	float getWidth(){/*return sprite.Width*/};
 
	

protected:

//	boost::shared_ptr<CSprite> sprite;
	float x_;
	float y_;
	float z_;
//	float width_;
//	float height_;
	
};

#endif