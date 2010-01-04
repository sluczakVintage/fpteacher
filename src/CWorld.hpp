/**
* @author Czarek Zawadka
* @date 2009.12.06
* @version 0.1_draft
* @brief klasa CWorld reprezentuje ca³y œwiat gry, jest singletonem.
*	
* @todo przemysle zarzadzanie CEntity -  kto powinien wywolywac konstruktory, 
*	kto powinien dodawac i usuwac CEntity ze swiata gry 
*/

#ifndef	WORLD_H
#define WORLD_H

#include <set>
#include <iostream>
#include <string>
#include "CEntity.hpp"
#include "CSingleton.hpp"
#include <boost/shared_ptr.hpp>

using namespace std; 
 
class CEntity;

//definicja struktury/klasy potrzebnej do porownywania <boost::shared_ptr<CEntity> w set< boost::shared_ptr<CEntity>, lessSharedPtr>
struct lessSharedPtr : public binary_function<boost::shared_ptr<CEntity>, boost::shared_ptr<CEntity>, bool>
{	
	///funkcja wywolywana przez set< boost::shared_ptr<CEntity>, lessSharedPtr> dla poronwywania shared_ptr
	bool operator()(const boost::shared_ptr<CEntity>& ptr1, const boost::shared_ptr<CEntity>& ptr2) const;
};

class CWorld : public CSingleton<CWorld>
{
	friend CSingleton<CWorld>;

public:

	///odrysowuje wszystkie CEntity
	void draw();	

	///odgrywa dŸwiêk we wszystkich CEntity
	void play();			

	///dodaje CEntity do wewnêtrznego kontenera, metoda (poki co) wolana przez ka¿d¹ CEntity w konstruktorze
	void addEntity(CEntity& entity);		

	///usuwa CEntity z wewnêtrznego kontenera, wywoluje destruktor CEntity
	void removeEntity(CEntity&);	

private:
	///kontener zawierajacy wszystkie CEntity ze œwiata
	//set<CEntity> entities_;
	set< boost::shared_ptr<CEntity>, lessSharedPtr> entities_;
	///konstruktor
	CWorld();
	///destruktor
	~CWorld();

};

#endif
