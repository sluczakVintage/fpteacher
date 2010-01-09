/** @file CSpriteMgr.cpp
* @author Sebastian £uczak
* @date 2010.01.04
* @version 0.1_draft
* @brief Klasa zarz¹dcy sprite'ow
* @todo Wydzielic loader plikow graficznych i zminimalizowac CSprite 
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
	cout << "CSpriteMgr::~CSpriteMgr: Destruktor CSpriteMgr" << endl;
}

HCSprite CSpriteMgr::getCSprite( const string name, const int frame_number, const int slice_w )
{
	string sprite_name;
	sprite_name = name;

	if(frame_number != 0)
	{
		ostringstream fr_nr;
		fr_nr << frame_number;
		sprite_name += fr_nr.str();
	}

    // wstawianie i wyszukiwanie
	NameIndexInsertRc rc = mNameIndex_.insert( std::make_pair( sprite_name, HCSprite() ) );
    if ( rc.second )
    {
        // dodanie nowego sprite'a
		//@TODO  boost::shared_ptr
		CSprite* csprite = mCSprites_.acquireHandle( rc.first->second );
		cout << "CSpriteMgr::getCSprite: Dodano uchwyt do nowego CSprite" << endl;
		if ( !csprite->openFile( name, frame_number, slice_w ) )
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

const std::string& CSpriteMgr::getName( HCSprite hcsprite ) const
        {  return ( mCSprites_.dereferenceHandle( hcsprite )->getSpriteName());  }

	const CSprite* CSpriteMgr::getCSpriteInstance( HCSprite hcsprite ) const
        {  return (mCSprites_.dereferenceHandle( hcsprite ) );  }
//~~CSpriteMgr.cpp
