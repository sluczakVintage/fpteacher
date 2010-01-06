/* 
 * "Portions Copyright (C) Scott Bilas, 2000"
 */


#ifndef CSPRITEMGR_H
#define CSPRITEMGR_H

#include <vector>
#include <map>
#include <cassert>

#include "CHandle.hpp"
#include "CHandleMgr.hpp"
#include "CSprite.hpp"
#include "CSingleton.hpp"

struct tagCSprite  {  };
typedef Handle <tagCSprite> HCSprite;

class CSpriteMgr : public CSingleton<CSpriteMgr>
{
	friend CSingleton<CSpriteMgr>;
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

// Konstruktory

    CSpriteMgr( void )  {  /* ... */  }
   ~CSpriteMgr( void );

// Zarzadzanie sprite'ami

	HCSprite getCSprite( const string name );
    void deleteCSprite( HCSprite hcsprite );

// Zapytania do sprite'a

    const std::string& getName( HCSprite hcsprite ) const
        {  return ( mCSprites_.dereferenceHandle( hcsprite )->getSpriteName());  }
    float getWidth( HCSprite hcsprite ) const
        {  return ( mCSprites_.dereferenceHandle( hcsprite )->getSpriteWidth());  }
    float getHeight( HCSprite hcsprite ) const
        {  return ( mCSprites_.dereferenceHandle( hcsprite )->getSpriteHeight());  }
    unsigned int getCSpriteHandle( HCSprite hcsprite ) const
        {  return ( mCSprites_.dereferenceHandle( hcsprite )->getTexID() );  }
};

#endif