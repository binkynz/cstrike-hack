#include "hash.h"

#include <cstring>

std::size_t hash::get( const char* string ) {

    auto ret = m_basis;

    const auto length = std::strlen( string );
    for ( std::size_t i = 0; i < length; ++i ) {

        ret ^= string[ i ];
        ret *= m_prime;

    }

    return ret;

}