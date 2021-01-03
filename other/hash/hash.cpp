#include "hash.h"

std::size_t hash::get( std::string_view string ) {

    std::size_t ret = m_basis;

    std::size_t length = std::strlen( string.data( ) );
    for ( std::size_t i = 0; i < length; ++i ) {

        ret ^= string[ i ];
        ret *= m_prime;

    }

    return ret;

}