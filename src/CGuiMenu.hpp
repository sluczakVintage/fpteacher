/**\file
* @author Sebastian Luczak
* @date 2010.03.03
* @version 0.1
* @class CGuiMenu CGuiMenu.hpp
* @brief klasa CGuiMenu opisuje wysuwane menu wyboru akcji
*	
*/

#ifndef CGUIMENU_H
#define CGUIMENU_H

#include <string>
#include <boost/smart_ptr.hpp>
#include <boost/logic/tribool.hpp>

#include "CSingleton.hpp"
#include "CStaticObject.hpp"
#include "CInput.hpp"
#include "CMouseObserver.hpp"

using namespace std;

//zrobic singleton
class CGuiMenu : public CSingleton<CGuiMenu>, public CMouseObserver
{
	friend class CSingleton<CGuiMenu>;
public:

	///wyrysowanie do bufora
	void drawIt();

	

private:

	///konstruktor 
	CGuiMenu();

	///destruktor
	~CGuiMenu();

	void show();

	void hide();

	/// odziedziczona wirtualna funkcja wykorzystywana przez CMouseObserver
	///@param CMO wskaznik na obiekt klasy CMouseEvent przechowujacej informacje o zdarzeniach zwiazanych z mysza
	virtual void refresh(CMouseEvent * CMO);
	/// odziedziczona wirtualna funkcja wykorzystywana przez CMouseObserver
	///@param over ????
	virtual void mouseIsOver(bool over);

	///t³o menu
	boost::shared_ptr<CStaticObject> menuBackground_;

	///wspolrzedna x'owa - os X przebiega z lewej do prawej
	float x_;

	///wspolrzedna y'owa - os Y przebiega z gory na dol
	float y_;

	boost::logic::tribool slide_;

	bool visible_;
};


#endif

//~~CGuiMenu.hpp
