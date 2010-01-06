/* 
 * "Portions Copyright (C) Scott Bilas, 2000"
 */

#include "CSpriteMgr.hpp"


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
		cout << "CSpriteMgr::getCSprite: Dodano uchwyt do nowego CSprite" << endl;
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
		cout << csprite->getSpriteName() << endl;
		mNameIndex_.erase( mNameIndex_.find( csprite->getSpriteName() ) );

        // usuniecie z bazy
		csprite->releaseSprite();
		//@TODO -> a mo¿e raczej delete CSprite
        mCSprites_.releaseHandle( hcsprite );

		cout << "CSpriteMgr::deleteCSprite: Uchwyt zostal zwolniony" << endl;
    }
}

