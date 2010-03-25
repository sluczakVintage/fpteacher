/**\file
* @author Sebastian Luczak
* @date 2010.03.10
* @version 0.1
* @class CGuiMenuButton CGuiMenuButton.hpp
* @brief klasa CGuiMenuButton opisuje przycisk w wysuwanym menu wyboru akcji
*	
*/

#ifndef CGUIMENUBUTTON_H
#define CGUIMENUBUTTON_H

#include <string>
#include <iostream>
#include <sstream>

#include "CStaticObject.hpp"
#include "CMouseObserver.hpp"
#include "CVideoSystem.hpp"
#include "CFontMgr.hpp"
#include "CLog.hpp"


class  CGuiMenuButton : public CMouseObserver
{
public:
	/// Konstruktor
	/// @param x wspolrzedna x przycisku
	/// @param y wspolrzedna y przycisku
	/// @param action enum oznaczajacy jaka akcja jest wywolywana przyciskiem
	/// @param cost koszt akcji wyswietlany na przycisku
	/// @param spritename nazwa grafiki przycisku
	CGuiMenuButton( const float x, const float y, const int cost, string spritename, string actName );

	///destruktor
	~CGuiMenuButton();
	
	///wyswietla przycisk
	void show( const float x_off );

	///ukrywa przycisk
	void hide();

	///wyrysowuje do bufora przycisk w obecnej pozycji
	void drawIt();


private:

	/// odziedziczona wirtualna funkcja wykorzystywana przez CMouseObserver
	///@param CMO wskaznik na obiekt klasy CMouseEvent przechowujacej informacje o zdarzeniach zwiazanych z mysza
	virtual void refresh(CMouseEvent * CMO);
	
	/// odziedziczona wirtualna funkcja wykorzystywana przez CMouseObserver
	///@param over informacja czy myszka jest nad obiektem
	virtual void mouseIsOver(bool over);

	/// wspolrzedna x przycisku
	float x_;

	/// przesuniecie x przycisku
	float xOffset_;
	
	/// wspolrzedna y przycisku
	float y_;

	///szerokosc
	float w_;

	///wysokosc
	float h_;

	//przezroczystosc przycisku
	int alpha_;

	/// grafika przycisku
	boost::shared_ptr<CStaticObject> defaultSprite_;

	/// grafika w momencie nacisniecia przycisku
	boost::shared_ptr<CStaticObject> onPressedSprite_;

	/// stan widocznosci przycisku (niewidoczny gdy nie ma many na akcje)
	bool visible_;

	/// stan przycisniecia przycisku (niewidoczny gdy nie ma many na akcje)
	bool pressed_;

	/// akcja aktywowana przyciskiem
	//int action_;

	/// wyswietlany koszt akcji
	string cost_;

	///nazwa akcji spod tego przycisku
	string actName_;

};
	

#endif

//~~CGuiMenuButton.hpp
