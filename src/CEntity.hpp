/**
* @author Czarek Zawadka
* @date 2009.12.06
* @version 0.1_draft
* @brief klasa CEntity jest abstrakcyjna blas¹ bazow¹ dla elementów, które mozna wyœwietliæ na ekranie
*	
*	
*/
#ifndef ENTITY_H
#define ENTITY_H


//#include "globals.hpp" ///linia do wywalenia
#include <string>
#include "CSprite.hpp"
#include "CWorld.hpp"

using namespace std;
 
class CSprite;
class CEntity
{
public:

	CEntity();
	CEntity(float x, float y,	float z, const string& filename  = NULL);
	virtual ~CEntity();
	virtual void draw();
	float getX() const;
	float getY() const;
	float getZ() const;
	float getHeight() const;
	float getWidth() const;
//	bool operator<(const CEntity& e2 ) const;///potrzebny, aby w CWorld mozna by³o uzywaæ std::set


protected:

	boost::shared_ptr<CSprite> sprite_;
	float x_;
	float y_;
	float z_;
//	float width_;
//	float height_;
	
};

bool operator<(const CEntity& e1, const CEntity& e2 );///potrzebny, aby w CWorld mozna by³o uzywaæ std::set


#endif