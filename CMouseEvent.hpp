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

	/// informuje o pozycji x myszy
	int x_;

	/// informuje o pozycji y myszy
	int y_;

};

#endif
