/** @file CAnimationMgr.cpp
* @author Sebastian luczak
* @date 2010.01.08
* @version 0.1_draft
* @brief Klasa zarz¹dcy animacji
* "Portions Copyright (C) Scott Bilas, 2000"
*/

#include "CAnimationMgr.hpp"


CAnimationMgr::~CAnimationMgr( void )
{
    // wyczysc baze sprite'ow
    NameIndex::iterator i, begin = mNameIndex_.begin(), end = mNameIndex_.end();
    for ( i = begin ; i != end ; ++i )
    {
        mCAnimations_.dereferenceHandle( i->second )->releaseAnimation();
    }
	cout << "CAnimationMgr::~CAnimationMgr: Destruktor CAnimationMgr" << endl;
}

HCAnimation CAnimationMgr::getCAnimation( const string name )
{
    // wstawianie i wyszukiwanie
	NameIndexInsertRc rc = mNameIndex_.insert( std::make_pair( name, HCAnimation() ) );
    if ( rc.second )
    {
        // dodanie nowego sprite'a
		//@TODO  boost::shared_ptr
		CAnimation* canimation = mCAnimations_.acquireHandle( rc.first->second );
		cout << "CAnimationMgr::getCAnimation: Dodano uchwyt do nowej CAnimation" << endl;
		if ( !canimation->openFile( rc.first->first ) )
        {
            deleteCAnimation( rc.first->second );
			rc.first->second = HCAnimation();
        }
    }
    return ( rc.first->second );
}

void CAnimationMgr::deleteCAnimation( HCAnimation hcanimation )
{
	CAnimation* canimation = mCAnimations_.dereferenceHandle( hcanimation );
	if ( canimation != 0 )
    {
        // usuniecie z wykazu nazw
		cout << canimation->getAnimationName() << endl;
		mNameIndex_.erase( mNameIndex_.find( canimation->getAnimationName() ) );

        // usuniecie z bazy
		canimation->releaseAnimation();
		
        mCAnimations_.releaseHandle( hcanimation );

		cout << "CAnimationMgr::deleteCAnimation: Uchwyt zostal zwolniony" << endl;
    }
}

const std::string& CAnimationMgr::getName( HCAnimation hcanimation ) const
        {  return ( mCAnimations_.dereferenceHandle( hcanimation )->getAnimationName());  }

CAnimation* CAnimationMgr::getCAnimationInstance( HCAnimation hcanimation )
		{  return (mCAnimations_.dereferenceHandle( hcanimation ) );  }

//~~CAnimationMgr.cpp
