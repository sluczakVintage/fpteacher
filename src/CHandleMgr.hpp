/** @file CHandleMgr.hpp
* @author Sebastian Luczak
* @author "Portions Copyright (C) Scott Bilas, 2000"
* @date 2010.01.04
* @version 0.6
* @class CHandleMgr CHandleMgr.hpp
* @brief CHandleMgr jest klasa zarzadcy uchwytow
*/

#ifndef	CHANDLEMGR_H
#define CHANDLEMGR_H

#include <vector>
#include <cassert>

using namespace std;

template <typename DATA, typename HANDLE>
class CHandleMgr 
{
private:
    /// UserVec konkretyzacja wektora danych do zarzadzania
	typedef std::vector<DATA>         UserVec;
	/// MagicVec konkretyzacja wektora magicznych liczb
    typedef std::vector<unsigned int> MagicVec;
	/// FreeVec konkretyzacja wektora wolnych uchwytow
	typedef std::vector<unsigned int> FreeVec;

    /// Wektor danych uzytkownika
	UserVec  m_UserData_;     
    /// Wektor magicznych liczb (pomagaja kontrolowac unikatowosc uchwytow)
	MagicVec m_MagicNumbers_; 
    /// Wektor wolnych uchwytow (zeby bylo szybciej przy tworzeniu nowych uchwytow)
	FreeVec  m_FreeSlots_;    

public:

	/// Konstruktor domyslny
	CHandleMgr()  
	{ 
		cout << "CHandleMgr::CHandleMgr: Konstruktor CHandleMgr" << endl;
		//@todo zmienic na cos bardziej szlachetnego...
		m_UserData_.reserve(1000);
	}

	/// Destruktor
   ~CHandleMgr()  
   { 
		// wyczysc wektor danych
		m_UserData_.erase(m_UserData_.begin(), m_UserData_.end());
		m_UserData_.clear();
		cout << "CHandleMgr::CHandleMgr: Destruktor CHandleMgr" << endl;
   }


    /// Pozwala pozyskac wskaznik do danej na podstawie uchwytu
	/// @param handle referencja do uchwytu
	/// @return wskaznik do danej
    DATA* acquireHandle( HANDLE& handle );

	/// Zwalnia uchwyt
	/// @param handle uchwyt do zwolnienia
    void  releaseHandle( HANDLE  handle );

    /// Dereferencja uchwytu na przechowywana dana
	/// @param handle uchwyt
	/// @return wskaznik do danej
    DATA* dereferenceHandle( HANDLE handle );

    /// Dereferencja uchwytu na przechowywana dana ( wersja const )
	/// @param handle uchwyt
	/// @return wskaznik do stalej wartosci wskazywanej
	const DATA* dereferenceHandle( HANDLE handle ) const;

    /// Zwraca ilosc uzytych uchwytow
	/// @return liczba uchwytow (unsigned int)
    unsigned int getUsedHandleCount() const
	{  return ( m_MagicNumbers_.size() - m_FreeSlots_.size() );  }

	/// Zwraca informacje czy manager posiada zarzadzane uchwyty
	/// @return Wartosc logiczna
    bool hasUsedHandles() const
        {  return ( !!getUsedHandleCount() );  }
};

template <typename DATA, typename HANDLE>
DATA* CHandleMgr<DATA, HANDLE>::acquireHandle( HANDLE& handle )
{
    // jezeli na liscie wolnych uchwytow sa jakies, skorzystaj z jednego z nich
    unsigned int index;
    if ( m_FreeSlots_.empty() )
    {
        index = m_MagicNumbers_.size();
        handle.init( index );
        m_UserData_.push_back( DATA() );
        m_MagicNumbers_.push_back( handle.getMagic() );
    }
	// jezeli nie ma, stworz nowy
    else
    {
        index = m_FreeSlots_.back();
        handle.init( index );
        m_FreeSlots_.pop_back();
        m_MagicNumbers_[ index ] = handle.getMagic();
    }
    return &(*(m_UserData_.begin() + index) );
}

template <typename DATA, typename HANDLE>
void CHandleMgr <DATA, HANDLE> :: releaseHandle( HANDLE handle )
{
    // okresl ktory uchwyt ma byc zwolniony
    unsigned int index = handle.getIndex();

    // sprawdz, czy na pewno jest prawidlowy
    assert( index < m_UserData_.size() );
    assert( m_MagicNumbers_[ index ] == handle.getMagic() );

    // jesli wszystko sie powiodlo, ustaw magiczna liczbe na 0, co oznacza, ze uchwyt jest pusty
	m_MagicNumbers_[ index ] = 0;
	// dodaj dany uchwyt do listy wolnych uchwytow
    m_FreeSlots_.push_back( index );
}

template <typename DATA, typename HANDLE>
inline DATA* CHandleMgr <DATA, HANDLE>:: dereferenceHandle( HANDLE handle )
{
    if ( handle.isNull() )  return ( 0 );

    // sprawdz czy dany uchwyt jest prawidlowy
	unsigned int index = handle.getIndex();
    if (   ( index >= m_UserData_.size() ) || ( m_MagicNumbers_[ index ] != handle.getMagic() ) )
    {
        // jesli nie, zwroc wskaznik na zero
        assert( 0 );
        return ( 0 );
    }
	//@todo to nie jest najlepsze rozwiazanie, bo wymaga niezmiennego rozmiaru wektora...
    return &(*( m_UserData_.begin() + index ) );
}

template <typename DATA, typename HANDLE>
inline const DATA* CHandleMgr <DATA, HANDLE>:: dereferenceHandle( HANDLE handle ) const
{
    // rzutowanie na wartosc stala by zwrocic wskaznik na stala wartosc wskazywana
    typedef CHandleMgr <DATA, HANDLE> ThisType;
     return ( const_cast <ThisType*> ( this )->dereferenceHandle( handle ) );
}

#endif

//~~CHandleMgr.hpp
