/**
* @author Czarek Zawadka
* @date 2009.12.06
* @version 0.1_draft
* @brief 
*	
*	
*/

#ifndef	WORLD_H
#define WORLD_H
//#include "globals.hpp"

#include <set>
#include <iostream>
#include <string>
#include "CEntity.hpp"
#include "CSingleton.hpp"
//#include <boost/shared_ptr.hpp>

using namespace std; 
 
class CEntity;

class CWorld : public CSingleton<CWorld>
{
	friend CSingleton<CWorld>;


public:

	void draw();			///odrysowuje wszystkie CEntity
	void play();			///odgrywa dŸwiêk we wszystkich CEntity
	void addEntity(const CEntity& entity);		///dodaje CEntity do wewnêtrznego kontenera, metoda (poki co) wolana przez ka¿d¹ CEntity w konstruktorze
	void removeEntity(CEntity&);	///usuwa CEntity z wewnêtrznego kontenera, wywoluje destruktor CEntity

private:

	set<CEntity> entities_;
	CWorld();
	~CWorld();

};
#endif