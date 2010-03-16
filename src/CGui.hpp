/**\file
* @author Rafal Malinowski
* @date 2009.01.08
* @version 0.6
* @class CGui CGui.hpp
* @brief klasa CGui bedzie odpowiedzialna za wyswietlanie i zarzadzanie gui
*	
*		
*/

#ifndef CGUI_H
#define CGUI_H

#include "CMouseObserver.hpp"
#include "CKeyObserver.hpp"
#include "CSingleton.hpp"
#include "CStaticEntity.hpp"
#include "CInput.hpp"
#include "CMouseEvent.hpp"
#include "CAudioSystem.hpp"
#include "CEngine.hpp"
#include "CLog.hpp"

class CMouseObserver;
class CKeyObserver;
class CInput;
using namespace std;

class CGui : public CSingleton<CGui> , public CMouseObserver, public CKeyObserver
{
	friend class CSingleton<CGui>;
	friend class CInput;
public:

	///Metoda inicjujaca encje zwiazane z gui
	void initGui();

private:

	///Konstruktor Domyslny
	CGui();
	///Destruktor
	~CGui();
	
	/// odziedziczona wirtualna funkcja wykorzystywana przez CMouseObserver
	///@param CMO wskaznik na obiekt klasy CMouseEvent przechowujacej informacje o zdarzeniach zwiazanych z mysza
	virtual void refresh(CMouseEvent * CMO);

	/// odziedziczona wirtualna funkcja wykorzystywana przez CMouseObserver
	///@param CMO wskaznik na obiekt klasy CMouseEvent przechowujacej informacje o zdarzeniach zwiazanych z mysza
	virtual void mouseIsOver(bool over);

	virtual void KeyPressed(SDLKey key, bool pressed);
};
#endif

//~~CGui.hpp