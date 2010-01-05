/**@file CAuditorium.cpp
* @author Czarek Zawadka
* @date 2010.01.04
* @version 0.1_draft
* 
* @brief klasa CAuditorium 
*/


#ifndef CAUDITORIUM_H
#define CAUDITORIUM_H

#include <map>
#include "CSingleton.hpp"
#include "CStaticEntity.hpp"
#include "CDynamicEntity.hpp"
#include "boost/multi_array.hpp"
#include "CField.hpp"


class CAuditorium : public CSingleton<CAuditorium>
{
	friend CSingleton<CAuditorium>;

public:

	void init(bool teacher);

	bool seatNewStudent(std::pair<int, int> at,CDynamicEntity& );

	///ilosc rzedow na sali
	const static int ROWS=5;
	
	///ilosc miejsc w rzedzie
	const static int COLUMNS=8;
	
	///stosunek odleglosci pomiedzy krawedzia rzedu a pierwszym miejscem do szerokosci rzedu
	const static float MARGIN;
	
	///stosunek odleglosci miedzy rzedami do szerokosci rzedu
	const static float TAB;
	
	///stosunek obszaru zaslonietego przez rzad z przodu do calej wysokosci
	const static float CUT_OFF;

private:
	//typedef boost::multi_array<std::pair boost::shared_ptr<CField> , 2>
	bool teacher_;
	boost::multi_array<boost::shared_ptr<CField> , 2> fields_;
 
};

/*
class Test
{
	~Test(){std::cout<<"~Test()"<<endl;}
};
*/
#endif