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
#include "CAuditorium.hpp"
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>



class CAuditorium;

class CField
{
	friend class CAuditorium;

public:
	
	CField(float x,float y,float z, float w, float h,int row, int column);
	~CField();
	CField(){};
	bool isMouseOver(int mouseX, int mouseY);
	bool getIsFree();
	bool getIsBusy();
	float getX();
	float getY();
	float getZ();
	float getWidth();
	float getHeight();
	std::pair<int, int>& getId(){return id_;};
	
	template<class Archive> 
	void serialize(Archive &ar, const unsigned int version)
	{
	
		ar & BOOST_SERIALIZATION_NVP(id_.first);
		ar & BOOST_SERIALIZATION_NVP(id_.second);
		ar & BOOST_SERIALIZATION_NVP(x_);
		ar & BOOST_SERIALIZATION_NVP(y_);
		ar & BOOST_SERIALIZATION_NVP(z_);
		ar & BOOST_SERIALIZATION_NVP( width_);
		ar & BOOST_SERIALIZATION_NVP(height_);
		ar & BOOST_SERIALIZATION_NVP(isFree_);
		ar & BOOST_SERIALIZATION_NVP(isBusy_);
	}
	
/*	template<class Archive> 
	void save(Archive & ar, const unsigned int version) const
    {
        // note, version is always the latest when saving
        ar  & driver_name;
        ar  & stops;
    }
    template<class Archive>
    void load(Archive & ar, const unsigned int version)
    {
        if(version > 0)
            ar & driver_name;
        ar  & stops;
    }
*/

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