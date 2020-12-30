#include "hash.h"

#include <cstring>

std::size_t hash::get( const char* txt ) {

    auto ret = basis;

    const auto length = std::strlen( txt );
    for ( std::size_t i = 0; i < length; ++i ) {

        ret ^= txt[ i ];
        ret *= prime;

    }

    return ret;

}