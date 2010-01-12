/** \file
* @author Sebastian Luczak
* @author "Portions Copyright (C) Scott Bilas, 2000"
* @date 2010.01.04
* @version 0.6
* @class Handle CHandle.hpp
* @brief Klasa uchwytu
*/

#ifndef	CHANDLE_H
#define CHANDLE_H


#include <cassert>

/// przechowuje rozmiary pol uchwytu
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
	/// @union unia pol wartosci uchwytu
    union
    {
		/// @struct 
        struct
        {
			/// Indeks uchwytu do umieszczenia w tablicy zasobow
            unsigned mIndex_ : MAX_BITS_INDEX;  
			/// Magiczna liczba do kontroli uchwytu
            unsigned mMagic_ : MAX_BITS_MAGIC;  
        };
		/// zmienna okreslajaca uchwyt (nieuzywane procz kontroli, czy uchwyt nie jest pusty)
        unsigned int mHandle_;
    };

public:

	/// Konstruktor domyslny
    Handle() : mHandle_( 0 )  {  }

	/// Metoda inicjujaca uchwyt
	/// @param index indeks uchwytu (unsigned int)
    void init( unsigned int index );

    /// Metoda pobierajaca indeks uchwytu
	/// @return indeks uchwytu (unsigned int)
	unsigned int getIndex () const  
		{  return (  mIndex_ );  }

	/// Metoda pobierajaca wartosc magicznej liczby
	/// @return magiczna liczba (unsigned int)
    unsigned int getMagic () const  
		{  return (  mMagic_ );  }

	/// Metoda pobierajaca wartosc uchwytu
	/// @return mHandle_ (unsigned int)
    unsigned int getHandle() const  
		{  return (  mHandle_ );  }

	/// Metoda sprawdzajaca czy uchwyt jest NULL
	/// @return czy uchwyt niezainicjowany (bool)
    bool isNull   () const  
		{  return ( !mHandle_ );  }

//	///Operator zwracajacy wartosc okreslajaca uchwyt
 //   operator unsigned int () const  {  return (  mHandle_ );  }
};

template <typename TAG>
void Handle <TAG> :: init( unsigned int index )
{
	// asercje
    assert( isNull());             
	// sprawdz czy indeks nie przekroczyl limitu
    assert( index <= MAX_INDEX);   
	
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

/// operator porownania uchwytow (rozny)
/// @param l uchwyt jako parametr z lewej strony operatora
/// @param r uchwyt jako parametr z prawej strony operatora
/// @return wartosc logiczna okreslajaca czy uchyty l i r sa rozne
template <typename TAG>
inline bool operator != ( Handle <TAG> l, Handle <TAG> r )
    {  return ( l.getHandle() != r.getHandle() );  }

/// operator porownania uchwytow (taki sam)
/// @param l uchwyt jako parametr z lewej strony operatora
/// @param r uchwyt jako parametr z prawej strony operatora
/// @return wartosc logiczna okreslajaca czy uchyty l i r sa takie same
template <typename TAG>
inline bool operator == ( Handle <TAG> l, Handle <TAG> r )
    {  return ( l.getHandle() == r.getHandle() );  }


#endif

//~~CHandle.hpp
