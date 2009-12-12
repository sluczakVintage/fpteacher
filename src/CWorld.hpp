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
	///odrysowuje wszystkie CEntity
	void draw();	

	///odgrywa dŸwiêk we wszystkich CEntity
	void play();			

	///dodaje CEntity do wewnêtrznego kontenera, metoda (poki co) wolana przez ka¿d¹ CEntity w konstruktorze
	void addEntity(const CEntity& entity);		

	///usuwa CEntity z wewnêtrznego kontenera, wywoluje destruktor CEntity
	void removeEntity(CEntity&);	

private:

	set<CEntity> entities_;
	CWorld();
	~CWorld();

};
#endif