/** @file CEntity.cpp
* @author Czarek Zawadka
* @date 2009.12.06
* @version 0.1_draft
* 
* @brief klasa CEntity jest blas¹ bazow¹ dla elementów, które mozna wyœwietliæ na ekranie
*
* @todo przemysle zarzadzanie CEntity -  kto powinien wywolywac konstruktory, 
*	kto powinien dodawac i usuwac CEntity ze swiata gry 	
*/


#include "CEntity.hpp"

using namespace std;

float CEntity::getX() const
{
	return x_;
}

float CEntity::getY() const
{
	return y_;
}

float CEntity::getZ() const
{
	return z_;
}



///@return true gdy e1.z_<e2.z_ lub e1 blizej punktu (0,0) na ekranie (lewego gornego rogu)
bool operator<(const CEntity& e1 ,const CEntity& e2 )
{
	float e1Z = e1.getZ();
	float e2Z = e2.getZ();

	if( e1Z < e2Z)
		return true;
	else
		if( e1Z> e2Z)
			return false;
		else
		{
			float e1X = e1.getX();
			float e1Y = e1.getY();
			float e2X = e2.getX();
			float e2Y = e2.getY();
			return (( e1X)*( e1X) +( e1Y)*( e1Y) < ( e2X)*( e2X) +( e2Y)*( e2Y)) ? true : false;
		}
}
/*
bool operator<(const boost::shared_ptr<CEntity>& ptr1, const boost::shared_ptr<CEntity>& ptr2)
{
	return (ptr1.get() < q.get());
}
*/