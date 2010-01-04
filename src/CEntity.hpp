/**
* @author Czarek Zawadka
* @date 2009.12.06
* @version 0.1_draft
* 
* @brief klasa CEntity jest blas¹ bazow¹ dla elementów, które mozna wyœwietliæ na ekranie
*	
* @todo przemysle zarzadzanie CEntity -  kto powinien wywolywac konstruktory, 
*	kto powinien dodawac i usuwac CEntity ze swiata gry
*/
#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include "CSprite.hpp"
#include "CWorld.hpp"

using namespace std;
 
class CSprite;

class CEntity
{
public:
	friend class CWorld;
	//	CEntity();
	///konstruktor 
	///@param trzy liczby float
	CEntity(float x, float y,	float z, const string& filename);
	///destruktor
	virtual ~CEntity();
	///wyrysowanie (spite'a) do bufora
	virtual void draw();
	///zwaraca wspolrzedna x'owa
	float getX() const;
	///zwaraca wspolrzedna y'owa
	float getY() const;
	///zwraca pseudo-wspolrzedna oznaczajaca bufor Z
	float getZ() const;
	///wysokosci (spite'a)
	float getHeight() const;
	///szerokosc (spite'a)
	float getWidth() const;
//	bool operator<(const CEntity& e2 ) const;///potrzebny, aby w CWorld mozna by³o uzywaæ std::set



protected:
	///wskaznik shared_ptr na CSprite odpowiadajacy danej CEntity
	boost::shared_ptr<CSprite> sprite_;
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
