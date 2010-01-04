/**
* @author Czarek Zawadka
* @date 2009.12.06
* @version 0.1_draft
* 
* @brief klasa CEntity jest abstrakcyjna klasa bazowa dla elementow, ktore mozna wyswietlic na ekranie
*	
* @todo przemysle zarzadzanie CEntity -  kto powinien wywolywac konstruktory, 
*	kto powinien dodawac i usuwac CEntity ze swiata gry
*/

#ifndef ENTITY_H
#define ENTITY_H

#include <string>

using namespace std;
 
class CEntity
{
public:
	friend class CWorld;
	///czysto wirtualne szeroko pojete rysowanie (animacja)
	virtual void draw() = 0;
	///zwaraca wspolrzedna x'owa
	float getX() const;
	///zwaraca wspolrzedna y'owa
	float getY() const;
	///zwraca pseudo-wspolrzedna oznaczajaca bufor Z
	float getZ() const;
	/////wysokosci (spite'a)
	//float getHeight() const;
	/////szerokosc (spite'a)
	//float getWidth() const;
//	bool operator<(const CEntity& e2 ) const;///potrzebny, aby w CWorld mozna by³o uzywaæ std::set



protected:
	///wspolrzedna x'owa - os X przebiega z lewej do prawej
	float x_;
	///wspolrzedna y'owa - os Y przebiega z gory na dol
	float y_;
	///pseudo-wspolrzedna oznaczajaca bufor Z
	float z_;
//	float width_;
//	float height_;
	
};

///przeladowanie operatora<, potrzebny, aby w CWorld mozna by³o uzywaæ std::set
bool operator<(const CEntity& e1, const CEntity& e2 );

#endif
