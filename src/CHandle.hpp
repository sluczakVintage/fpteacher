/** @file CSpriteMgr.cpp
* @author Sebastian £uczak
* @date 2010.01.04
* @version 0.1_draft
* @brief Klasa zarz¹dcy sprite'ów
* @todo Wydzielic loader plikow graficznych i zminimalizowac CSprite 
* "Portions Copyright (C) Scott Bilas, 2000"
*/

#ifndef	CHANDLE_H
#define CHANDLE_H


#include <cassert>

template <typename TAG>
class Handle
{
    union
    {
        enum
        {
            // sizes to use for bit fields
            ///@TODO Powinny byc pobierane z pliku
			MAX_BITS_INDEX = 16,
            MAX_BITS_MAGIC = 16,

            // sizes to compare against for asserting dereferences
            MAX_INDEX = ( 1 << MAX_BITS_INDEX) - 1,
            MAX_MAGIC = ( 1 << MAX_BITS_MAGIC) - 1,
        };

        struct
        {
            unsigned mIndex_ : MAX_BITS_INDEX;  // index into resource array
            unsigned mMagic_ : MAX_BITS_MAGIC;  // magic number to check
        };
        unsigned int mHandle_;
    };

public:

// Lifetime.

    Handle( void ) : mHandle_( 0 )  {  }

    void init( unsigned int index );

// Query.

    unsigned int getIndex ( void ) const  {  return (  mIndex_ );  }
    unsigned int getMagic ( void ) const  {  return (  mMagic_ );  }
    unsigned int getHandle( void ) const  {  return (  mHandle_ );  }
    bool         isNull   ( void ) const  {  return ( !mHandle_ );  }

    operator unsigned int ( void ) const  {  return (  mHandle_ );  }
};

template <typename TAG>
void Handle <TAG> :: init( unsigned int index )
{
    assert( isNull() );             // don't allow reassignment
    assert( index <= MAX_INDEX );   // verify range

    static unsigned int s_AutoMagic = 0;
    if ( ++s_AutoMagic > MAX_MAGIC )
    {
        s_AutoMagic = 1;    // 0 is used for "null handle"
    }

    mIndex_ = index;
    mMagic_ = s_AutoMagic;
}

template <typename TAG>
inline bool operator != ( Handle <TAG> l, Handle <TAG> r )
    {  return ( l.getHandle() != r.getHandle() );  }

template <typename TAG>
inline bool operator == ( Handle <TAG> l, Handle <TAG> r )
    {  return ( l.getHandle() == r.getHandle() );  }


#endif

//~~CHandle.hpp
