/* 
 * "Portions Copyright (C) Scott Bilas, 2000"
 */

#include <vector>
#include <map>
#include <cassert>

#include "CHandle.hpp"
#include "CHandleMgr.hpp"
#include "CSprite.hpp"


struct tagCSprite  {  };
typedef Handle <tagCSprite> HCSprite;

class CSprite;
class CSpriteMgr
{

// Definicja CSprite'a i bazki.
	
    typedef HandleMgr <CSprite, HCSprite> HCSpriteMgr;

// Index by name into db.

    // operator porownania string'ow w indeksie nazw
    struct istring_less
    {
        bool operator () ( const std::string& l, const std::string& r ) const
            {  return ( l.compare(r) < 0 );  }
    };

    typedef std::map <std::string, HCSprite, istring_less > NameIndex;
    typedef std::pair <NameIndex::iterator, bool> NameIndexInsertRc;

// dane prywatne 
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

CSpriteMgr::~CSpriteMgr( void )
{
    // wyczysc baze sprite'ow
    NameIndex::iterator i, begin = mNameIndex_.begin(), end = mNameIndex_.end();
    for ( i = begin ; i != end ; ++i )
    {
        mCSprites_.dereferenceHandle( i->second )->releaseSprite();
    }
}

HCSprite CSpriteMgr::getCSprite( const string name )
{
    // wstawianie i wyszukiwanie
	NameIndexInsertRc rc = mNameIndex_.insert( std::make_pair( name, HCSprite() ) );
    if ( rc.second )
    {
        // dodanie nowego sprite'a
		//@TODO  boost::shared_ptr
		CSprite* csprite = mCSprites_.acquireHandle( rc.first->second );
		if ( !csprite->openFile( rc.first->first ) )
        {
            deleteCSprite( rc.first->second );
			rc.first->second = HCSprite();
        }
    }
    return ( rc.first->second );
}

void CSpriteMgr::deleteCSprite( HCSprite hcsprite )
{
	CSprite* csprite = mCSprites_.dereferenceHandle( hcsprite );
	if ( csprite != 0 )
    {
        // usuniecie z wykazu nazw
		mNameIndex_.erase( mNameIndex_.find( csprite->getSpriteName() ) );

        // usuniecie z bazy
		csprite->releaseSprite();
		//@TODO -> a mo¿e raczej delete CSprite
        mCSprites_.releaseHandle( hcsprite );
    }
}

