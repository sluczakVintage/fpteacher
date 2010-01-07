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
#include "CTimer.hpp"
#include <boost/serialization/split_member.hpp>


class CField;

class CAuditorium : public CSingleton<CAuditorium>
{
	friend CSingleton<CAuditorium>;
	friend class boost::serialization::access;

	//friend boost::serialization::access<CAuditorium>;
	//friend static void boost::serialization::access::destroy<CAuditorium>(const CAuditorium *ca);
	
public:

	void loadStaticEntities();
	void init(bool teacher);

	//bool seatNewStudent(std::pair<int, int> at);
	bool seatNewStudent(int row, int col);

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

	template<class Archive>
    void save(Archive & ar, const unsigned int version) const
	{
	
		ar & BOOST_SERIALIZATION_NVP(teacher_);
	
		for(int j = 0; j<ROWS; j++)
		{
			for (int i = 0; i<COLUMNS;i++)
			{
				CField c_field = *(fields_[j][i]);
				ar & BOOST_SERIALIZATION_NVP(c_field);
			}
		}
	}
	
	template<class Archive>
    void load(Archive & ar, const unsigned int version)
    {
		CAuditorium * t = CAuditorium::getInstance();
		ar & BOOST_SERIALIZATION_NVP(teacher_);
		t->teacher_ = this->teacher_; 
		for(int j = 0; j<ROWS; j++)
		{
			for (int i = 0; i<COLUMNS;i++)
			{
				CField * c_field = new CField();
				ar & BOOST_SERIALIZATION_NVP(c_field);
				boost::shared_ptr<CField> ptr(c_field);
				t->fields_[j][i] = ptr;
				if(!(t->fields_[j][i]->isFree_))
				{
					t->fields_[j][i]->isFree_=true;
					t->seatNewStudent(j,i);
				}
			}
		}
		t->loadStaticEntities();
		free(this);
	}
	
	BOOST_SERIALIZATION_SPLIT_MEMBER();
	
	//typedef boost::multi_array<std::pair boost::shared_ptr<CField> , 2>
	
	bool teacher_;

	boost::multi_array<boost::shared_ptr<CField> , 2> fields_;
	
	CAuditorium();
	
	~CAuditorium();

	//void *operator new(size_t size);

};

namespace boost { namespace serialization {

	template<class Archive>
	inline void load_construct_data(
			Archive & ar, CAuditorium * t, const unsigned int file_version
		){
		}

}}

#endif