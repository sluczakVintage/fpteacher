/** @file HandleMgr.hpp
* @author Sebastian £uczak
* @date 2010.01.04
* @version 0.1_draft
* @brief Klasa zarz¹dcy uchwytow
* "Portions Copyright (C) Scott Bilas, 2000"
*/

#ifndef	CHANDLEMGR_H
#define CHANDLEMGR_H

#include <vector>
#include <cassert>


template <typename DATA, typename HANDLE>
class HandleMgr 
{
private:
    // private types
	typedef std::vector <DATA>         UserVec;
    typedef std::vector <unsigned int> MagicVec;
    typedef std::vector <unsigned int> FreeVec;

    // private data
    UserVec  m_UserData_;     // data we're going to get to
    MagicVec m_MagicNumbers_; // corresponding magic numbers
    FreeVec  m_FreeSlots_;    // keeps track of free slots in the db

public:

// Lifetime.

    HandleMgr( void )  { 
		//@TODO zmienic na cos bardziej szlachetnego...
		cout << "CHandleMgr::CHandleMgr: Konstruktor CHandleMgr" << endl;
		m_UserData_.reserve(1000);
	}
   ~HandleMgr( void )  { 
	m_UserData_.erase(m_UserData_.begin(), m_UserData_.end());
	m_UserData_.clear();
	cout << "CHandleMgr::CHandleMgr: Destruktor CHandleMgr" << endl;
   }

// Handle methods.

    // acquisition
    DATA* acquireHandle( HANDLE& handle );
    void  releaseHandle( HANDLE  handle );

    // dereferencing
    DATA*       dereferenceHandleNonConst( HANDLE handle );
	DATA* dereferenceHandle( HANDLE handle );
    const DATA* dereferenceHandle( HANDLE handle ) const;

    // inne zapytania
    unsigned int getUsedHandleCount( void ) const
        {  return ( m_MagicNumbers_.size() - m_FreeSlots_.size() );  }
    bool hasUsedHandles( void ) const
        {  return ( !!getUsedHandleCount() );  }
};

template <typename DATA, typename HANDLE>
DATA* HandleMgr<DATA, HANDLE>::acquireHandle( HANDLE& handle )
{
    // if free list is empty, add a new one otherwise use first one found

    unsigned int index;
    if ( m_FreeSlots_.empty() )
    {
        index = m_MagicNumbers_.size();
        handle.init( index );
        m_UserData_.push_back( DATA() );
        m_MagicNumbers_.push_back( handle.getMagic() );
    }
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
void HandleMgr <DATA, HANDLE> :: releaseHandle( HANDLE handle )
{
    // which one?
    unsigned int index = handle.getIndex();

    // make sure it's valid
    assert( index < m_UserData_.size() );
    assert( m_MagicNumbers_[ index ] == handle.getMagic() );

    // ok remove it - tag as unused and add to free list
    m_MagicNumbers_[ index ] = 0;
    m_FreeSlots_.push_back( index );
}

template <typename DATA, typename HANDLE>
inline DATA* HandleMgr <DATA, HANDLE>:: dereferenceHandleNonConst( HANDLE handle )
{
    if ( handle.isNull() )  return ( 0 );

    // check handle validity - $ this check can be removed for speed
    // if you can assume all handle references are always valid.
    unsigned int index = handle.getIndex();
    if (   ( index >= m_UserData_.size() ) || ( m_MagicNumbers_[ index ] != handle.getMagic() ) )
    {
        // no good! invalid handle == client programming error
        assert( 0 );
        return ( 0 );
    }

    return &(*( m_UserData_.begin() + index ) );
}

template <typename DATA, typename HANDLE>
inline DATA* HandleMgr <DATA, HANDLE>:: dereferenceHandle( HANDLE handle )
{
    if ( handle.isNull() )  return ( 0 );

    // check handle validity - $ this check can be removed for speed
    // if you can assume all handle references are always valid.
    unsigned int index = handle.getIndex();
    if (   ( index >= m_UserData_.size() ) || ( m_MagicNumbers_[ index ] != handle.getMagic() ) )
    {
        // no good! invalid handle == client programming error
        assert( 0 );
        return ( 0 );
    }

    return &(*( m_UserData_.begin() + index ) );
}

template <typename DATA, typename HANDLE>
inline const DATA* HandleMgr <DATA, HANDLE>:: dereferenceHandle( HANDLE handle ) const
{
    // this lazy cast is ok - non-const version does not modify anything
    typedef HandleMgr <DATA, HANDLE> ThisType;
     return ( const_cast <ThisType*> ( this )->dereferenceHandle( handle ) );
}

#endif

//~~CHandleMgr.hpp
