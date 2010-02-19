/**\file
* @author Sebastian Luczak
* @author "Portions Copyright (C) Scott Bilas, 2000"
* @date 2010.01.04
* @version 0.6
* @class CSpriteMgr CSpriteMgr.hpp
* @brief Klasa zarzadcy sprite'ow
* @todo Wydzielic loader plikow graficznych i zminimalizowac CSprite 
*/


#ifndef CSPRITEMGR_H
#define CSPRITEMGR_H

#include <vector>
#include <map>
#include <cassert>
//naglowki klas aplikacji
#include "CSingleton.hpp"
#include "CHandle.hpp"
#include "CHandleMgr.hpp"
#include "CSprite.hpp"
#include "utils.hpp"


using namespace std;
/// konkretyzuje znacznik uchwytu do obiektu typu CSprite
struct tagCSprite  {  };
/// skonkretyzowany uchwyt do obiektow typu CSprite
typedef Handle <tagCSprite> HCSprite;

class CSprite;
class CSpriteMgr : public CSingleton<CSpriteMgr>
{
	friend class CSingleton<CSpriteMgr>;

private:
	/// Konstruktor domyslny
    CSpriteMgr()  {  
	cout << "CSpriteMgr::CSpriteMgr: Konstruktor CSpriteMgr" << endl;
	}
	/// Destruktor
   ~CSpriteMgr();

	/// konkretyzacja typu bazy uchwytow do CSprite.
    typedef CHandleMgr <CSprite, HCSprite> HCSpriteMgr;

	/// NameIndex konkretyzacja slownika przechowujaca obiekty typu CSprite indeksowane przy pomocy nazwy (string)
	typedef std::map <std::string, HCSprite, utils::string_less > NameIndex;
	/// NameIndexInsertRc konretyzacja pary przechowujaca iterator na obiekt NameIndex i 
	/// wartosc logiczna okreslana przez to, czy element slownika juz istnial, czy jest nowy. 
	/// Uzywane przy dodawaniu CSprite do managera
    typedef std::pair <NameIndex::iterator, bool> NameIndexInsertRc;

	/// Manager CSprite
	HCSpriteMgr mCSprites_;
	/// Manager uchwytow do CSprite indeksowany nazwa CSprite
	NameIndex  mNameIndex_;

public:


	/// Metoda zwracajaca uchwyt do CSprite, jesli dany uchwyt jeszcze nie istnieje, tworzy nowy
	/// @param name nazwa CSprite'a
	/// @param frame_number parametr uzywany przy zestawach animacji, okresla na ile klatek ma byc pociety CSprite
	/// @param slice_w parametr uzywany przy zestawach animacji, okresla jaka jest szerokosc klatki
	/// @return HCSprite uchwyt do obiektu typu CSprite
	HCSprite getCSprite( const std::string name, const int frame_number = 0, const int slice_w = 0 );
	
	/// Metoda usuwajaca podany uchwyt i jego CSprite z bazy
	/// @param hcsprite uchwyt do CSprite
    void deleteCSprite( HCSprite hcsprite );

	/// Metoda zwracajaca nazwe sprite'a na podstawie uchwytu
	/// @param hcsprite uchwyt do CSprite
	/// @return referencja do obiektu typu string zawierajacego nazwe CSprite'a
    const std::string& getName( HCSprite hcsprite ) const;
	
	/// Metoda zwracajaca wskaznik do stalej wartosci wskazywanej typu CSprite o danym uchwycie
	/// @param hcsprite uchwyt do CSprite
	/// @return wskaznik do stalej wartosci wskazywanej typu CSprite
	const CSprite* getCSpritePtr( HCSprite hcsprite ) const;

};


#endif

//~~CSpriteMgr.hpp
