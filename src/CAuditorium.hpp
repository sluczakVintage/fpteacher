/**
* @author Czarek Zawadka
* @date 2009.12.06
* @version 0.1_draft
* 
* @brief klasa CAuditorium 
*/


#ifndef CAUDITORIUM_H
#define CAUDITORIUM_H

#include <map>
#include "CSingleton.hpp"
#include "CStaticEntity.hpp"


class CAuditorium : public CSingleton<CAuditorium>
{
	friend CSingleton<CAuditorium>;

public:

	void init();

private:


};
#endif