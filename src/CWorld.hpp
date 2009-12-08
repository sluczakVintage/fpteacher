/**
* @author Czarek Zawadka
* @date 2009.12.06
* @version 0.1_draft
* @brief 
*	
*	
*/

#ifndef	WORLD
#define WORLD

#include <map>
#include <iostream>
#include <string>
#include "CEntity.hpp"


//using namespace std; 
 
class CWorld
{

public:

	CWorld();
	~CWorld();
	void draw();
	void play();
private:
	std::map< int, CEntity > entities_;
};
#endif