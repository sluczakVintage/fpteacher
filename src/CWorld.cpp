#include "CWorld.hpp"

using namespace std;

CWorld::CWorld()
{
	entities_.clear();
}

CWorld::~CWorld(void)
{
	
}

void CWorld::draw()
{
  set<CEntity>::iterator it;
 
  for ( it=entities_.begin() ; it != entities_.end(); it++ ) 
	  it->draw();
}

void play()
{

}

void CWorld::addEntity(const CEntity& entity)
{
	//if(entities_ != NULL && entity != NULL)
	if(entities_.find(entity) == entities_.end())
		entities_.insert(entity);
	else 
		cout<<"CWorld::addEntity: encja juz istnieje \n";
}


void CWorld::removeEntity(CEntity& entity)
{
	entities_.erase(entity);
	entity.~CEntity();
}