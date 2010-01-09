/**
* @author Czarek Zawadka
* @date 2009.12.06
* @version 0.1_draft
* 
* @brief abstrakcyjna klasa bazowa dla elementow na ekranie. 
*	
* @todo przemysle zarzadzanie CEntity -  kto powinien wywolywac konstruktory, 
*	kto powinien dodawac i usuwac CEntity ze swiata gry
* @todo dynamiczna deserializacja tej klasy oraz pochodnych
*/

#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <boost/weak_ptr.hpp>
using namespace std;
 
class CEntity
{
public:

	friend class CWorld;
	friend class CAuditorium;
	
	CEntity(float x, float y,	float z, const string& filename);

	CEntity();

	virtual ~CEntity();
	friend class CWorld;
	///czysto wirtualne szeroko pojete rysowanie (animacja)
	virtual void draw() = 0;
	///zwaraca wspolrzedna x'owa
	float getX() const;
	///zwaraca wspolrzedna y'owa
	float getY() const;
	///zwraca pseudo-wspolrzedna oznaczajaca bufor Z
	float getZ() const;
	
	string getType();

	string getFilename();



protected:
	///wspolrzedna x'owa - os X przebiega z lewej do prawej
	float x_;
	///wspolrzedna y'owa - os Y przebiega z gory na dol
	float y_;
	///pseudo-wspolrzedna oznaczajaca bufor Z
	float z_;

	///string oznaczajacy typ encji - potrzebne do serializacji
	string type_;	

	///strin oznaczajacy plik z ktorego sie inicjalizuje encje - potrzebne do serializacji 
	string filename_;

	boost::weak_ptr<CEntity> selfPtr_;
};

///przeladowanie operatora<, potrzebny, aby w CWorld mozna by³o uzywaæ std::set
bool operator<(const CEntity& e1, const CEntity& e2 );


#endif
