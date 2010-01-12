/** @file CAnimationMgr.hpp
* @author Sebastian luczak
* @author "Portions Copyright (C) Scott Bilas, 2000"
* @date 2010.01.08
* @version 0.1_draft
* @class CAnimationMgr CAnimationMgr.hpp
* @brief Klasa zarz¹dcy animacji
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


using namespace std;
///@struct FESTER
struct tagCAnimation  {  };
/// @typedef FESTER
typedef Handle <tagCAnimation> HCAnimation;

class CAnimation;
class CAnimationMgr : public CSingleton<CAnimationMgr>
{
	friend class CSingleton<CAnimationMgr>;
private:
	// Konstruktory

	///FESTER
   CAnimationMgr( void )  { 
		cout << "CAnimationMgr::CAnimationMgr: Konstruktor CAnimationMgr" << endl;
   }
   ~CAnimationMgr( void );

	// Definicja bazy uchwytow do CAnimation.
    typedef HandleMgr <CAnimation, HCAnimation> HCAnimationMgr;

// indeks oparty na nazwach plikow

    // operator porownania string'ow w indeksie nazw
    struct istring_less
    {
        bool operator () ( const std::string& l, const std::string& r ) const
            {  return ( l.compare(r) < 0 );  }
    };

    typedef std::map <std::string, HCAnimation, istring_less > NameIndex;
    typedef std::pair <NameIndex::iterator, bool> NameIndexInsertRc;

// skladowe prywatne 
	HCAnimationMgr mCAnimations_;
	NameIndex  mNameIndex_;

public:


// Zarzadzanie uchwytami animacji
	///FESTER
	HCAnimation getCAnimation( const std::string name );
	///FESTER
    void deleteCAnimation( HCAnimation hcanimation );

// Zapytania do animacji
	///FESTER
    const std::string& getName( HCAnimation hcanimation ) const;
	///FESTER
	CAnimation* getCAnimationInstance( HCAnimation hcanimation );

};


#endif

//~~CAnimationMgr.hpp
