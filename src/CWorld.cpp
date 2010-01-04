/** @file CWorld.cpp
* @author Czarek Zawadka
* @date 2009.12.06
* @version 0.1_draft
* @brief klasa CWorld reprezentuje ca³y œwiat gry, jest singletonem.
*	
* @todo przemysle zarzadzanie CEntity -  kto powinien wywolywac konstruktory, 
*	kto powinien dodawac i usuwac CEntity ze swiata gry 
*/

#include "CWorld.hpp"

using namespace std;

CWorld::CWorld()
{
}

CWorld::~CWorld(void)
{
//	entities_.clear();
}

///odrysowanie calego swiata poprzez wywolanie na kazdej CEntity metody draw()
void CWorld::draw()
{
  set< boost::shared_ptr<CEntity>, lessSharedPtr>::iterator it; 
  for ( it=entities_.begin() ; it != entities_.end(); it++ ) 
	  (*it)->draw();
}

///tu beda odgrywane wszystkie dŸwiêki
void play()
{
}

///dodawanie encji na swiat. 
void CWorld::addEntity(CEntity& entity)
{
	//Jezeli encja juz istnieje(lub jakas o tych samych x_,y_,z_ oraz o tej samej wysokosci/szerokosci)
	//to kolejna nie zostanie dodana do swiata
	boost::shared_ptr<CEntity> ptr (&entity);
	 if((entities_.insert(ptr)).second)
	 {
		cout<<"CWorld::addEntity: dodano encje \n";
	 }
	 else
		cout<<"CWorld::addEntity: encja juz istnieje \n";
	
	 //cout<<"CWorld::addEntity: sprawdzenie operatorow:>"<<(ptr<ptr)<<"<"<<endl;
	 /*if(entities_.find(ptr) == entities_.end())
	{	
		entities_.insert(ptr);
		cout<<"CWorld::addEntity: dodano encje \n";
	}
	else 
		cout<<"CWorld::addEntity: encja juz istnieje \n";
		*/
}

///usuniecie encji ze swiata, powoduje wywolanie jej destruktora
void CWorld::removeEntity(CEntity& entity)
{
	boost::shared_ptr<CEntity> ptr (&entity);
	entities_.erase(ptr);
	//entity.~CEntity();
}

///funkcja wywolywana przez set< boost::shared_ptr<CEntity>, lessSharedPtr> dla poronwywania shared_ptr
///wywoluje odpowiedznia metode porownujaca obiekty CEntity - deklaracja w pliku CEntity
bool lessSharedPtr::operator()(const boost::shared_ptr<CEntity>& ptr1, const boost::shared_ptr<CEntity>& ptr2) const
{	
		return ( (*(ptr1.get())) < (*(ptr2.get())) );

}