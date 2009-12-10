/**
* @author Rafal Malinowski
* @date 2009.12.07
* @version 0.1_draft
* @brief klasa CInput odpowiada za odbieranie sygna³ów z myszy i klawiatury
*	
*		
*/
#ifndef CINPUT
#define CINPUT

//#include <iostream>
//#include <string>
//#include "globals.hpp"
#include "keys.hpp"

using namespace std;
 

class CInput
{
public:
	CInput();

	~CInput();

	int getKeyState(eKey key);

	int getMouseX();

	int getMouseY();

	bool mouseClicked();

	void update();

private:

	int mouseX_;
	int mouseY_;
	char m_Keystates[200];
	
};

#endif