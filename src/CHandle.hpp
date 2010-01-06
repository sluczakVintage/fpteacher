/* 
 * "Portions Copyright (C) Scott Bilas, 2000"
 */
#include <cassert>

template <typename TAG>
class Handle
{
    union
    {
        enum
        {
            // sizes to use for bit fields
            MAX_BITS_INDEX = 16,
            MAX_BITS_MAGIC = 16,

            // sizes to compare against for asserting dereferences
            MAX_INDEX = ( 1 << MAX_BITS_INDEX) - 1,
            MAX_MAGIC = ( 1 << MAX_BITS_MAGIC) - 1,
        };

        struct
        {
            unsigned m_Index_ : MAX_BITS_INDEX;  // index into resource array
            unsigned m_Magic_ : MAX_BITS_MAGIC;  // magic number to check
        };
        unsigned int m_Handle_;
    };

public:

// Lifetime.

    Handle( void ) : m_Handle_( 0 )  {  }

    void init( unsigned int index );

// Query.

    unsigned int getIndex ( void ) const  {  return (  m_Index_ );  }
    unsigned int getMagic ( void ) const  {  return (  m_Magic_ );  }
    unsigned int getHandle( void ) const  {  return (  m_Handle_ );  }
    bool         isNull   ( void ) const  {  return ( !m_Handle_ );  }

    operator unsigned int ( void ) const  {  return (  m_Handle_ );  }
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

    m_Index_ = index;
    m_Magic_ = s_AutoMagic;
}

template <typename TAG>
inline bool operator != ( Handle <TAG> l, Handle <TAG> r )
    {  return ( l.getHandle() != r.getHandle() );  }

template <typename TAG>
inline bool operator == ( Handle <TAG> l, Handle <TAG> r )
    {  return ( l.getHandle() == r.getHandle() );  }

