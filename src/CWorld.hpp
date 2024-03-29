/**\file
* @author Czarek Zawadka
* @date 2009.12.06
* @version 0.6
* @class CWorld CWorld.hpp
* @brief klasa CWorld reprezentuje caly swiat gry
*
* klasa jest odpowiedzialna za skladowanie obiektow wyswietlanych na ekranie
*  - CEntity oraz jej pochodnych.
*
*
* @todo przemysle zarzadzanie CEntity -  kto powinien wywolywac konstruktory, 
*	kto powinien dodawac i usuwac CEntity ze swiata gry 
*/

#ifndef	WORLD_H
#define WORLD_H

#include <set>
#include <map>
#include <vector>

#include <iostream>
#include <string>
#include "CEntity.hpp"
#include "CVideoOverlay.hpp"
#include "CSingleton.hpp"

#include <boost/smart_ptr.hpp>
#include <boost/foreach.hpp>

using namespace std; 
 
class CEntity;
class CVideoOverlay;

///definicja typu boost::shared_ptr<CEntity> 
typedef boost::shared_ptr<CEntity> CEntityPtr;
typedef map<int, boost::shared_ptr<CVideoOverlay>> OverlayMap;

///definicja struktury potrzebnej do porownywania <boost::shared_ptr<CEntity> w set< boost::shared_ptr<CEntity>, lessSharedPtr>
struct lessSharedPtr : public binary_function<boost::shared_ptr<CEntity>, boost::shared_ptr<CEntity>, bool>
{	
	///funkcja wywolywana przez set< boost::shared_ptr<CEntity>, lessSharedPtr> dla poronwywania shared_ptr
	bool operator()(const boost::shared_ptr<CEntity>& ptr1, const boost::shared_ptr<CEntity>& ptr2) const;
};

class CWorld : public CSingleton<CWorld>
{
	friend class CSingleton<CWorld>;

public:

	///odrysowuje wszystkie CEntity i CDynamicObject
	void draw();	

	///@deprecated odgrywa dzwiek we wszystkich CEntity
	//void play();			

	///dodaje CEntity do wewnetrznego kontenera, metoda (poki co) wolana przez kazda CEntity w konstruktorze
	//std::pair<bool, CEntityPtr> addEntity(CEntity& entity);		
	
	///dodaje encje do swiata gry
	void addEntity(CEntity& entity);

	///dodaje object do swiata gry
	void addOverlay(boost::shared_ptr<CVideoOverlay> overlay);

	///usuwa CEntity z wewnetrznego kontenera, wywoluje destruktor CEntity	
	void removeEntity(CEntity&);	

	///usuwa CDynamicObject z wewnetrznego kontenera
	void removeOverlay(int uid);	

private:

	///kontener zawierajacy wszystkie CEntity ze swiata
	set<CEntityPtr, lessSharedPtr> entities_;

	///kontener zawierajacy wszystkie obiekty animowane ze swiata
	OverlayMap overlays_;

	///konstruktor domyslny
	CWorld();

	///destruktor
	~CWorld();

};

#endif

//~~CWorld.hpp
