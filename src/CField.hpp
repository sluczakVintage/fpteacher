
/*
#ifndef FIELD_H
#define FIELD_H

#include "CMouseObserver.hpp"
#include <string>
#include <iostream>
#include "utils.hpp"
#include "CAuditorium.hpp"
#include "CEntity.hpp"
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include "CMouseEvent.hpp"
#include "CAudioSystem.hpp"
#include "CSoundNetworkEvent.hpp"
#include "CStudentNetworkEvent.hpp"
#include "CTimer.hpp"

class CAuditorium;
class CMouseObserver;
//class CInput;
//class CNetworkEvent;

typedef boost::shared_ptr<CEntity> EntityPtr;

class CField: public CMouseObserver
{
	friend class CAuditorium;
	friend class CInput;
	friend class boost::serialization::access;

public:
	
	///Konstruktor inicjalizujacy wszystkie parametry
	CField(float x,float y,float z, float width, float height,int row, int column);
	
	///Konstruktor domyslny
	CField();

	///Destruktor
	~CField();

	///metoda zwraca true gdy argumenty sa wewnatrz prostokata pola
	bool isMouseOver(int mouseX, int mouseY);
	
	///@return czy pole jest zajete przez studenta
	bool getIsFree();

	///@return czy student jest zajety przez jakas animacje etc. @ref todo
	bool getIsBusy();

	///@return wspolrzedna X pola - liczone od lewej
	float getX();

	///@return wspolrzedna Y pola - liczone od gory
	float getY();

	///@return wartosc bufora glebokosci
	float getZ();

	///@return szerokosc pola
	float getWidth();

	///@return pozycja czlowieka, potrzeba do odtwarzania dzwieku 3d
	int getPosition();

	///@return odleglosc czlowieka, potrzebna do odtwarzania dzwieku 3d
	int getDistance();

	///@return wysokosc pola
	float getHeight();

	///@return kopie id_ pola
	std::pair<int, int>& getId(){return id_;};


private:

	///szablon umozliwiajacy serializacje i deserializacje klasy
	///@param &ar archiwum z przestrzeni nazw boost::archive
	///@param version pole umozliwiajace wersjonowanie klasy, poki co niewykorzystane
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


	///id miejsca jest para int'ow oznaczajaca rzad i miejsce na sali liczone od (0,0) 
	///czyli miejsca po lewej stronie w najnizszym rzedzie patrzac od strony wykladowcy
	std::pair<int, int> id_;

	///wspolrzedna x'owa - os X przebiega z lewej do prawej
	float x_;

	///wspolrzedna y'owa - os Y przebiega z gory na dol
	float y_;

	///pseudo-wspolrzedna oznaczajaca bufor Z
	float z_;

	///szerokosc pola
	float width_;

	///wysokosc pola
	float height_;

	///flaga pokazujaca czy pole jest wolne
	bool isFree_;

	///flaga pokazujaca czys tudent jest zajety,  @ref todo
	bool isBusy_;
	
	EntityPtr entPtr_ ; 

	virtual void refresh(CMouseEvent * CMO);
};

#endif
/*