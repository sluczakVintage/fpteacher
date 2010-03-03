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

#include "CVideoOverlay.hpp"
#include "CStaticObject.hpp"

using namespace std;

class CGuiMenu
{
public:

	///konstruktor 
	CGuiMenu();

	///destruktor
	~CGuiMenu();

	///wyrysowanie do bufora
	virtual void drawIt();

	bool show();

	bool hide();

protected:
	///t³o menu
	CStaticObject menuBackground_;

	///wspolrzedna x'owa - os X przebiega z lewej do prawej
	float x_;

	///wspolrzedna y'owa - os Y przebiega z gory na dol
	float y_;

	bool visible_;
};


#endif

//~~CGuiMenu.hpp
