/**
* @author Czarek Zawadka
* @date 2009.12.06
* @version 0.1_draft
* @class CWorld CWorld.hpp
* @brief klasa CWorld reprezentuje caly swiat gry, jest singletonem.
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
typedef boost::shared_ptr<CEntity> CEntityPtr;

//definicja struktury/klasy potrzebnej do porownywania <boost::shared_ptr<CEntity> w set< boost::shared_ptr<CEntity>, lessSharedPtr>
///@struct CZAREK
struct lessSharedPtr : public binary_function<boost::shared_ptr<CEntity>, boost::shared_ptr<CEntity>, bool>
{	
	///funkcja wywolywana przez set< boost::shared_ptr<CEntity>, lessSharedPtr> dla poronwywania shared_ptr
	bool operator()(const boost::shared_ptr<CEntity>& ptr1, const boost::shared_ptr<CEntity>& ptr2) const;
};

class CWorld : public CSingleton<CWorld>
{
	friend class CSingleton<CWorld>;

public:

	///odrysowuje wszystkie CEntity
	void draw();	

	///odgrywa dzwiek we wszystkich CEntity
	void play();			

	///dodaje CEntity do wewnetrznego kontenera, metoda (poki co) wolana przez kazda CEntity w konstruktorze
	//std::pair<bool, CEntityPtr> addEntity(CEntity& entity);		
	void addEntity(CEntity& entity);
	///usuwa CEntity z wewnetrznego kontenera, wywoluje destruktor CEntity
	void removeEntity(CEntity&);	

private:
	///kontener zawierajacy wszystkie CEntity ze swiata
	//set<CEntity> entities_;
	set<CEntityPtr, lessSharedPtr> entities_;
	///konstruktor
	CWorld();
	///destruktor
	~CWorld();

};

#endif
