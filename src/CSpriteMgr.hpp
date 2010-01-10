/** @file CSpriteMgr.hpp
* @author Sebastian £uczak
* @date 2010.01.04
* @version 0.3_draft
* @brief Klasa zarz¹dcy sprite'ow
* @todo Wydzielic loader plikow graficznych i zminimalizowac CSprite 
* "Portions Copyright (C) Scott Bilas, 2000"
*/


#ifndef CSPRITEMGR_H
#define CSPRITEMGR_H

#include <vector>
#include <map>
#include <cassert>

#include "CSingleton.hpp"
#include "CHandle.hpp"
#include "CHandleMgr.hpp"
#include "CSprite.hpp"


using namespace std;

struct tagCSprite  {  };
typedef Handle <tagCSprite> HCSprite;

class CSprite;
class CSpriteMgr : public CSingleton<CSpriteMgr>
{
	friend CSingleton<CSpriteMgr>;
private:
	// Konstruktory

    CSpriteMgr( void )  {  
	cout << "CSpriteMgr::CSpriteMgr: Konstruktor CSpriteMgr" << endl;
	}
   ~CSpriteMgr( void );

	// Definicja bazy uchwytow do CSprite.
    typedef HandleMgr <CSprite, HCSprite> HCSpriteMgr;

// indeks oparty na nazwach plikow

    // operator porownania string'ow w indeksie nazw
    struct istring_less
    {
        bool operator () ( const std::string& l, const std::string& r ) const
            {  return ( l.compare(r) < 0 );  }
    };

    typedef std::map <std::string, HCSprite, istring_less > NameIndex;
    typedef std::pair <NameIndex::iterator, bool> NameIndexInsertRc;

// skladowe prywatne 
	HCSpriteMgr mCSprites_;
	NameIndex  mNameIndex_;

public:


// Zarzadzanie sprite'ami

	HCSprite getCSprite( const std::string name, const int frame_number = 0, const int slice_w = 0 );
    void deleteCSprite( HCSprite hcsprite );

// Zapytania do sprite'a

    const std::string& getName( HCSprite hcsprite ) const;
	const CSprite* getCSpriteInstance( HCSprite hcsprite ) const;

};


#endif

//~~CSpriteMgr.hpp
