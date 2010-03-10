/** @file CAnimationMgr.cpp
* @author Sebastian luczak
* @date 2010.01.08
* @version 0.6
* @brief Klasa zarzadcy animacji
* "Portions Copyright (C) Scott Bilas, 2000"
*/

#include "CAnimationMgr.hpp"
using namespace logging;


/// Destruktor
CAnimationMgr::~CAnimationMgr()
{
    // wyczysc baze sprite'ow
    NameIndex::iterator i, begin = mNameIndex_.begin(), end = mNameIndex_.end();
    for ( i = begin ; i != end ; ++i )
    {
        mCAnimations_.dereferenceHandle( i->second )->releaseAnimation();
    }
	CLog::getInstance()->sss << "CAnimationMgr::~CAnimationMgr: Destruktor CAnimationMgr" << endl;
	logs(CLog::getInstance()->sss.str(), INFO);
}
//Konstruktor domyslny
CAnimationMgr::CAnimationMgr()
  { 
		CLog::getInstance()->sss << "CAnimationMgr::CAnimationMgr: Konstruktor CAnimationMgr" << endl;
		logs(CLog::getInstance()->sss.str(), INFO);
		
   }
/// Metoda zwracajaca uchwyt do CAnimation, jesli dany uchwyt jeszcze nie istnieje, tworzy nowy
HCAnimation CAnimationMgr::getCAnimation( const std::string name )
{
    // wstawianie i wyszukiwanie
	NameIndexInsertRc rc = mNameIndex_.insert( std::make_pair( name, HCAnimation() ) );
    if ( rc.second )
    {
        // dodanie nowego sprite'a
		//@todo  boost::shared_ptr
		CAnimation* canimation = mCAnimations_.acquireHandle( rc.first->second );
		CLog::getInstance()->sss << "CAnimationMgr::getCAnimation: Dodano uchwyt do nowej CAnimation" << endl;
		logs(CLog::getInstance()->sss.str(), INFO);
		if ( !canimation->openFile( rc.first->first ) )
        {
            deleteCAnimation( rc.first->second );
			rc.first->second = HCAnimation();
        }
    }
    return ( rc.first->second );
}

/// Metoda usuwajaca podany uchwyt i jego CAnimation z bazy
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

		CLog::getInstance()->sss << "CAnimationMgr::deleteCAnimation: Uchwyt zostal zwolniony" << endl;
		logs(CLog::getInstance()->sss.str(), INFO);
    }
}

/// Metoda zwracajaca nazwe zestawu animacji na podstawie uchwytu
const std::string& CAnimationMgr::getName( HCAnimation hcanimation ) const
        {  return ( mCAnimations_.dereferenceHandle( hcanimation )->getAnimationName());  }

/// Metoda zwracajaca nazwe zestawu animacji na podstawie uchwytu
CAnimation* CAnimationMgr::getCAnimationPtr( HCAnimation hcanimation )
		{  return (mCAnimations_.dereferenceHandle( hcanimation ) );  }

//~~CAnimationMgr.cpp
