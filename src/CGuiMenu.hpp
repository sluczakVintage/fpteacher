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
#include <vector>

#include <boost/smart_ptr.hpp>
#include <boost/foreach.hpp>
#include <boost/logic/tribool.hpp>

#include "CSingleton.hpp"
#include "CStaticObject.hpp"
#include "CMouseObserver.hpp"
#include "CGuiMenuButton.hpp"

#include "CLog.hpp"

using namespace std;

class CGuiMenu : public CSingleton<CGuiMenu>, public CMouseObserver
{
	friend class CSingleton<CGuiMenu>;
public:

	/// Wyrysowanie menu do bufora w obecnej pozycji
	void drawIt();

private:

	///konstruktor 
	CGuiMenu();

	///destruktor
	~CGuiMenu();

	/// Powoduje wysuwanie sie menu
	void show();

	/// Powoduje chowanie sie menu
	void hide();

	/// odziedziczona wirtualna funkcja wykorzystywana przez CMouseObserver
	///@param CMO wskaznik na obiekt klasy CMouseEvent przechowujacej informacje o zdarzeniach zwiazanych z mysza
	virtual void refresh(CMouseEvent * CMO);
	
	/// odziedziczona wirtualna funkcja wykorzystywana przez CMouseObserver
	///@param over informacja czy myszka jest nad obiektem
	virtual void mouseIsOver(bool over);

	///t³o menu
	boost::shared_ptr<CStaticObject> menuBackground_;

	///wspolrzedna x'owa - os X przebiega z lewej do prawej
	float x_;

	///wspolrzedna y'owa - os Y przebiega z gory na dol
	float y_;
	
	///informuje czy menu sie wysuwa, wsuwa czy spoczywa 
	boost::logic::tribool slide_;
	
	///informuje czy menu jest widoczne
	bool visible_;
	
	vector<boost::shared_ptr<CGuiMenuButton>> buttons_;
};


#endif

//~~CGuiMenu.hpp
