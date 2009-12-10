/**
* @author Rafal Malinowski
* @date 2009.12.07
* @version 0.1_draft
* @brief klasa CInput odpowiada za odbieranie sygna³ów z myszy i klawiatury
*	
*		
*/
#ifndef	CINPUT_H
#define CINPUT_H

#include <iostream>
#include <string>

using namespace std;
 

class CInput
{
public:
	CInput();

	~CInput();

	bool isKeyDown(string key);
	
	bool isKeyUp(string key);

	int getMouseX();

	int getMouseY();

	bool mouseClicked();

	bool update();

private:

	int mouseX_;
	int mouseY_;
	char keyState_[256];
	
	
};

#endif