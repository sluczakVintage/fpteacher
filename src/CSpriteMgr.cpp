/** @file CSpriteMgr.cpp
* @author Sebastian luczak
* @author "Portions Copyright (C) Scott Bilas, 2000"
* @date 2010.01.04
* @version 0.6
* @brief Klasa zarzadcy sprite'ow
* @todo Wydzielic loader plikow graficznych i zminimalizowac CSprite 
*/

#include "CSpriteMgr.hpp"
using namespace logging;

CSpriteMgr::~CSpriteMgr()
{
    // wyczysc baze sprite'ow
    NameIndex::iterator i, begin = mNameIndex_.begin(), end = mNameIndex_.end();
    for ( i = begin ; i != end ; ++i )
    {
        mCSprites_.dereferenceHandle( i->second )->releaseSprite();
    }
	CLog::getInstance()->sss << "CSpriteMgr::~CSpriteMgr: Destruktor CSpriteMgr" <<endl;
	logs(CLog::getInstance()->sss.str(), INFO);
	
}

CSpriteMgr::CSpriteMgr()  {  
	CLog::getInstance()->sss << "CSpriteMgr::CSpriteMgr: Konstruktor CSpriteMgr" << endl;
	logs(CLog::getInstance()->sss.str(), INFO);
}

HCSprite CSpriteMgr::getCSprite( const std::string name, const int frame_number, const int slice_w )
{
	string sprite_name;
	sprite_name = name;

	// modyfikacja nazwy CSprite na wypadek, gdy plik podawany jako parametr jest sekwencja klatek
	// (potrzebne przy zarzadzaniu obiektami CSprite w CSpriteMgr
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
		CSprite* csprite = mCSprites_.acquireHandle( rc.first->second );
		CLog::getInstance()->sss << "CSpriteMgr::getCSprite: Dodano uchwyt do nowego CSprite"  <<endl;
		logs(CLog::getInstance()->sss.str(), INFO);

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
        mCSprites_.releaseHandle( hcsprite );

		CLog::getInstance()->sss << "CSpriteMgr::deleteCSprite: Uchwyt zostal zwolniony"   <<endl;
		logs(CLog::getInstance()->sss.str(), INFO);
		
    }
}

const std::string& CSpriteMgr::getName( HCSprite hcsprite ) const
        {  return ( mCSprites_.dereferenceHandle( hcsprite )->getSpriteName());  }

const CSprite* CSpriteMgr::getCSpritePtr( HCSprite hcsprite ) const
        {  return (mCSprites_.dereferenceHandle( hcsprite ) );  }


CSprite* CSpriteMgr::getCSpritePtr( HCSprite hcsprite ) 
	{  return (mCSprites_.dereferenceHandle( hcsprite ) );  }

void CSpriteMgr::reloadAllCSprites()
{
	std::pair<std::string, HCSprite> p;

	BOOST_FOREACH( p, mNameIndex_)
	{
		getCSpritePtr(p.second)->releaseSprite();

	}

	BOOST_FOREACH( p, mNameIndex_)
	{
		getCSpritePtr(p.second)->reloadSprite();

	}
}
//~~CSpriteMgr.cpp
