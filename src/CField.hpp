/**
* @author Czarek Zawadka
* @date 2009.12.06
* @version 0.1_draft
* 
* @brief klasa CField 
*/

#ifndef FIELD_H
#define FIELD_H

#include <string>
#include <iostream>
#include "utils.hpp"

class CField
{
public:
	
	CField(float x,float y,float z, float w, float h,int row, int column);
	bool isMouseOver(int mouseX, int mouseY);
	bool getIsFree();
	bool getIsBusy();
	float getX();
	float getY();
	float getZ();
	float getWidth();
	float getHeight();
	std::pair<int, int>& getId(){return id_;};
 
private:

	///id miejsca jest para int'ow oznaczajaca rzad i miejsce na sali liczone od (0,0)
	std::pair<int, int> id_;
	///wspolrzedna x'owa - os X przebiega z lewej do prawej
	float x_;
	///wspolrzedna y'owa - os Y przebiega z gory na dol
	float y_;
	///pseudo-wspolrzedna oznaczajaca bufor Z
	float z_;

	float width_;

	float height_;

	bool isFree_;

	bool isBusy_;///bycmoze to powinna byc cecha CEntity/CDynamicEntity


};
#endif