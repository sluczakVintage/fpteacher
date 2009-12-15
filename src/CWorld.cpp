#include "CWorld.hpp"

using namespace std;

CWorld::CWorld()
{
}

CWorld::~CWorld(void)
{
	entities_.clear();
}

///odrysowanie calego swiata poprzez wywolanie na kazdej CEntity metody draw()
void CWorld::draw()
{
  set<CEntity>::iterator it; 
  for ( it=entities_.begin() ; it != entities_.end(); it++ ) 
	  it->draw();
}

///tu beda odgrywane wszystkie dŸwiêki
void play()
{
}

///dodawanie encji na swiat. 
void CWorld::addEntity(const CEntity& entity)
{
	//Jezeli encja juz istnieje(lub jakas o tych samych x_,y_,z_ oraz o tej samej wysokosci/szerokosci)
	//to kolejna nie zostanie dodana do swiata
	if(entities_.find(entity) == entities_.end())
		entities_.insert(entity);
	else 
		cout<<"CWorld::addEntity: encja juz istnieje \n";
}

///usuniecie encji ze swiata, powoduje wywolanie jej destruktora
void CWorld::removeEntity(CEntity& entity)
{
	entities_.erase(entity);
	entity.~CEntity();
}
