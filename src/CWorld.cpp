/** @file CWorld.cpp
* @author Czarek Zawadka
* @date 2009.12.06
* @version 0.6
* @brief klasa CWorld reprezentuje caly swiat gry, jest singletonem.
*	
*/

#include "CWorld.hpp"

using namespace std;

//konstruktor domyslny
CWorld::CWorld()
{

}

//destruktor
CWorld::~CWorld(void)
{
	entities_.clear();
}

//odrysowanie calego swiata poprzez wywolanie na kazdej CEntity metody draw()
void CWorld::draw()
{
  set< boost::shared_ptr<CEntity>, lessSharedPtr>::iterator it; 
  for ( it=entities_.begin() ; it != entities_.end(); it++ ) 
  {	  
	  (*it)->draw();
  }
	std::pair< int, boost::shared_ptr<CDynamicObject> > p;
  BOOST_FOREACH( p, objects_)
	{
		p.second->draw();
	}
}

///tu beda odgrywane wszystkie dzwieki
//void play()
//{
//
//}

//dodawanie encji na swiat.
void CWorld::addEntity(CEntity& entity)
{
	//Jezeli encja juz istnieje(lub jakas o tych samych x_,y_,z_ oraz o tej samej wysokosci/szerokosci)
	//to kolejna nie zostanie dodana do swiata
	boost::shared_ptr<CEntity> ptr (&entity);
	entity.selfPtr_ = boost::weak_ptr<CEntity>(ptr);
	 if((entities_.insert(ptr)).second)
	 {
		cout<<"CWorld::addEntity: dodano encje \n";
	 }
	 else
		cout<<"CWorld::addEntity: encja juz istnieje \n";
	
}

//usuniecie encji ze swiata, powoduje wywolanie jej destruktora
void CWorld::removeEntity(CEntity& entity)
{
	boost::shared_ptr<CEntity> ptr (&entity);
	entities_.erase(ptr);
	//entity.~CEntity();
}

//dodawanie nakladki
void CWorld::addObject(CDynamicObject& object)
{
	boost::shared_ptr<CDynamicObject> ptr (&object);
	
	if(objects_.insert(std::make_pair(object.uid_,ptr)).second)
	 {
		cout<<"CWorld::addObject: dodano obiekt \n";
	 }
	 else
		cout<<"CWorld::addObject: obiekt juz istnieje \n";
	
}

//usuniecie obiektu ze swiata, powoduje wywolanie jej destruktora
void CWorld::removeObject(int uid)
{
	objects_.erase(uid);
	//entity.~CEntity();
}

//funkcja wywolywana przez set< boost::shared_ptr<CEntity>, lessSharedPtr> dla poronwywania shared_ptr
//wywoluje odpowiedznia metode porownujaca obiekty CEntity - deklaracja w pliku CEntity
bool lessSharedPtr::operator()(const boost::shared_ptr<CEntity>& ptr1, const boost::shared_ptr<CEntity>& ptr2) const
{	
		return ( (*(ptr1.get())) < (*(ptr2.get())) );

}

//~~CWorld.cpp
