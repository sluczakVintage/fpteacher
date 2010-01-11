/** @file CHandle.hpp
* @author Sebastian luczak
* @date 2010.01.04
* @version 0.1_draft
* @class Handle CHandle.hpp
* @brief Klasa uchwytu
* "Portions Copyright (C) Scott Bilas, 2000"
*/

#ifndef	CHANDLE_H
#define CHANDLE_H


#include <cassert>

enum
{
            /// rozmiary pol
            ///@todo Powinny byc pobierane z pliku
			MAX_BITS_INDEX = 16,
            MAX_BITS_MAGIC = 16,

            /// rozmiary do porownan przy asercjach
            MAX_INDEX = ( 1 << MAX_BITS_INDEX) - 1,
            MAX_MAGIC = ( 1 << MAX_BITS_MAGIC) - 1,
};

template <typename TAG>
class Handle
{
    union
    {
        struct
        {
			/// Indeks uchwytu do umieszczenia w tablicy zasobow
            unsigned mIndex_ : MAX_BITS_INDEX;  
			/// Magiczna liczba do kontroli uchwytu
            unsigned mMagic_ : MAX_BITS_MAGIC;  
        };
        unsigned int mHandle_;
    };

public:

	/// Konstruktor domyslny
    Handle() : mHandle_( 0 )  {  }
	/// Metoda inicjujaca
	/// @param index indeks uchwytu (unsigned int)
    void init( unsigned int index );

    /// Metoda pobierajaca indeks uchwytu
	/// @return indeks uchwytu (unsigned int)
	unsigned int getIndex () const  {  return (  mIndex_ );  }
	/// Metoda pobierajaca wartosc magicznej liczby
	/// @return magiczna liczba (unsigned int)
    unsigned int getMagic () const  {  return (  mMagic_ );  }
	/// Metoda pobierajaca wartosc uchwytu
	/// @return mHandle_ (unsigned int)
    unsigned int getHandle() const  {  return (  mHandle_ );  }
	/// Metoda sprawdzajaca czy uchwyt jest NULL
	/// @return czy uchwyt niezainicjowany (bool)
    bool isNull   () const  {  return ( !mHandle_ );  }
	///FESTER
    operator unsigned int () const  {  return (  mHandle_ );  }
};

template <typename TAG>
void Handle <TAG> :: init( unsigned int index )
{
	// asercje
    assert( isNull() );             
	// sprawdz czy indeks nie przekroczyl limitu
    assert( index <= MAX_INDEX );   
	
	// wartosc statyczna pomagajaca przypisac kolejne magiczne liczby
    static unsigned int s_AutoMagic = 0;
    if ( ++s_AutoMagic > MAX_MAGIC )
    {
        s_AutoMagic = 1;    // 0 oznacza pusty uchwyt
    }
	// przypisz odpowiednie wartosci
    mIndex_ = index;
    mMagic_ = s_AutoMagic;
}

template <typename TAG>
/// operator porownania uchwytow (rozny)
inline bool operator != ( Handle <TAG> l, Handle <TAG> r )
    {  return ( l.getHandle() != r.getHandle() );  }

template <typename TAG>
/// operator porownania uchwytow (taki sam)
inline bool operator == ( Handle <TAG> l, Handle <TAG> r )
    {  return ( l.getHandle() == r.getHandle() );  }


#endif

//~~CHandle.hpp
