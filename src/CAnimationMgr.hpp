/** @file CAnimationMgr.hpp
* @author Sebastian Luczak
* @author "Portions Copyright (C) Scott Bilas, 2000"
* @date 2010.01.08
* @version 0.6
* @class CAnimationMgr CAnimationMgr.hpp
* @brief Klasa zarzadcy animacji
*/


#ifndef CANIMATIONMGR_H
#define CANIMATIONMGR_H

#include <vector>
#include <map>
#include <cassert>

#include "CSingleton.hpp"
#include "CHandle.hpp"
#include "CHandleMgr.hpp"
#include "CAnimation.hpp"
#include "utils.hpp"

#include "CLog.hpp"

using namespace std;
/// konretyzuje znacznik uchwytu do typu CAnimation
struct tagCAnimation  {  };
/// HCAnimation skonkretyzowany uchwyt do obiektow typu CSprite
typedef Handle <tagCAnimation> HCAnimation;

class CAnimation;
class CAnimationMgr : public CSingleton<CAnimationMgr>
{
	friend class CSingleton<CAnimationMgr>;
private:
	/// Konstruktor domyslny
   CAnimationMgr();
   /// Destruktor
   ~CAnimationMgr();

	/// HCAnimationMgr konkretyzacja typu bazy uchwytow do CSprite.
    typedef CHandleMgr <CAnimation, HCAnimation> HCAnimationMgr;

// indeks oparty na nazwach plikow

	/// NameIndex konkretyzacja slownika przechowujaca obiekty typu CAnimation indeksowane przy pomocy nazwy (string)
	typedef std::map <std::string, HCAnimation, utils::string_less > NameIndex;

	/// NameIndexInsertRc konretyzacja pary przechowujaca iterator na obiekt NameIndex i 
	/// wartosc logiczna okreslana przez to, czy element slownika juz istnial, czy jest nowy. 
	/// Uzywane przy dodawaniu CSprite do managera
    typedef std::pair <NameIndex::iterator, bool> NameIndexInsertRc;

	/// Manager CAnimation
	HCAnimationMgr mCAnimations_;
	/// Manager uchwytow do CAnimation indeksowany nazwa CAnimation
	NameIndex  mNameIndex_;

public:

	/// Metoda zwracajaca uchwyt do CAnimation, jesli dany uchwyt jeszcze nie istnieje, tworzy nowy
	/// @param name nazwa CAnimation (zestaw animacij)
	/// @return HCAnimation uchwyt do obiektu typu CAnimation
	HCAnimation getCAnimation( const std::string name );

	/// Metoda usuwajaca podany uchwyt i jego CAnimation z bazy
	/// @param hcanimation uchwyt do CAnimation
    void deleteCAnimation( HCAnimation hcanimation );

	/// Metoda zwracajaca nazwe zestawu animacji na podstawie uchwytu
	/// @param hcanimation uchwyt do CAnimation
	/// @return referencja do obiektu typu string zawierajacego nazwe CAnimation
    const std::string& getName( HCAnimation hcanimation ) const;
	
	/// Metoda zwracajaca wskaznik do stalej wartosci wskazywanej typu CAnimation o danym uchwycie
	CAnimation* getCAnimationPtr( HCAnimation hcanimation );

};


#endif

//~~CAnimationMgr.hpp
