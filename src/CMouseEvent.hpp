/**
* @author Rafal Malinowski
* @date 2009.01.08
* @version 0.1_draft
* @brief klasa CMouseEvent odpowiada za przesylanie informacji na temat akcji myszy z klasy CInput do innych
*	
*		
*/
#ifndef C_MOUSE_EVENT
#define C_MOUSE_EVENT


#include <iostream>


using namespace std;



class CMouseEvent
{

public:

	/// konstruktor domyslny
	CMouseEvent();

	/// destruktor domyslny
	~CMouseEvent();

	/// informuje o pozycji x myszy w momencie klikniecia
	int pressedX_;

	/// informuje o pozycji y myszy w momencie klikniecia
	int pressedY_;

	/// informuje o pozycji x myszy w momencie puszczania przycisku
	int releasedX_;

	/// informuje o pozycji y myszy w momencie puszczania przycisku
	int releasedY_;

};

#endif
