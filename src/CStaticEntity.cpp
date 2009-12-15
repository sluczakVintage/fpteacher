#include "CStaticEntity.hpp"

/*
CStaticEntity::~CStaticEntity()
{
	//super.~CEnity();
	cout<<"destruktor: CStaticEntity"<<endl;
}
*/

///konstruktor jedynie wywoluje konstruktor klasy bazowej
CStaticEntity::CStaticEntity(float x, float y,	float z, const string& filename):CEntity(x,y,z,filename)
{
}
