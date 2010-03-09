/**\file
* @author Rafal Malinowski
* @date 2009.01.07
* @version 0.6
* @class CMouseObserver CMouseObserver.hpp
* @brief klasa CMouseObserver jest abstrakcyjna klasa po ktorej beda dziedziczyc wszystkie klasy zainteresowane obsluga myszy
*	
*		
*/
#ifndef CMOUSE_OBSERVER
#define CMOUSE_OBSERVER

#include <cassert>
#include "SDL.h"
#include <iostream>
#include "CSingleton.hpp"
#include "COGLWindow.hpp"
#include "CInput.hpp"
#include "CMouseEvent.hpp"
#include "CLog.hpp"

using namespace std;

class CMouseObserver
{
	friend class CInput;

public:

	/// metoda ustalajaca czy obiekt/obserator jest zainteresowany przesylaniem informacji o tym czy mysz najechala nad obiekt
	///@param x true jesli obiekt chce dostawac informacje na temat ruchu mysza nad nim i false jesli nie jest tym zainteresowany
	void setMoveObserver (bool x);

	/// metoda zwracajaca informacje czy obiekt jest zainteresowany obserwowaniem ruchu myszy nad nim
	bool getMoveObserver();

	/// UWAGA moze nie funkcjonowac poprawnie, w razie watpliwosci do Maliny
	/// metoda mowiaca ze mysz jest nad obiektem
	void setMoveIsOver (bool x);

	/// metoda ustawiajaca id observatora
	void setId();

	/// metoda zwracajaca id observatora
	/// @return id obserwatora
	int getId();

	/// metoda zwracajaca ilosc observatorow
	/// @return ilosc observatorow
	int getCounter();

	/// UWAGA moze nie funkcjonowac poprawnie, w razie watpliwosci do Maliny
	/// metoda mowiaca czy mysz jest nad obiektem
	/// @return true jesli tak i false jesli nie
	bool getMoveIsOver();

protected:

	/// licznik observatorow
	static int obsCounter_;

	/// id observatora
	int id_;

	/// wirtualna metoda wywolywana przez klase CInput we wszystkich dziedziczacych klasach (wywolywana podczas klikniec)
	/// @param CMO obiekt klasy CMouseEvent przechowujacy informacje o miejscach klikniecia i takich tam
	virtual void refresh(CMouseEvent * CMO) = 0;

	/// wirtualna metoda wywolywana przez klase CInput we wszystkich dziedziczacych klasach (wywolywana podczas ruchu)
	/// @param true jesli mysz wjechala nad obiekt i false gdy wlasnie z niego zjechala
	virtual void mouseIsOver(bool over) = 0;

	/// destruktor wirutalny
	virtual ~CMouseObserver();

	/// flaga mowiaca czy nad obiektem znajduje sie myszka
	bool mouseIsOver_;

	/// flaga mowiaca czy observatora interesuje tylko klikanie myszy czy takze ruch
	bool moveObserver_;

};

#endif

//~~CMouseObserver.hpp