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
#include "boost/multi_array.hpp"
#include "CField.hpp"

class Test
{
	~Test(){std::cout<<"~Test()"<<endl;}
};

class CAuditorium : public CSingleton<CAuditorium>
{
	friend CSingleton<CAuditorium>;

public:

	void init(bool teacher);

	const static int ROWS=5;
	const static int COLUMNS=8;
	const static float MARGIN;
	const static float TAB;
	const static float CUT_OFF;
private:

	bool teacher_;
	boost::multi_array<boost::shared_ptr<CField> , 2> fields_;
 
};
#endif