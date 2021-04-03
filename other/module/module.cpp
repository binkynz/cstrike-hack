#include "module.h"

module_info::module_info( std::size_t the_module ) {

	m_module = the_module;
	m_bitmap = reinterpret_cast< std::uint8_t* >( the_module );
	m_dos_header = reinterpret_cast< PIMAGE_DOS_HEADER >( the_module );
	m_base = m_dos_header->e_lfanew;
	m_nt_headers = reinterpret_cast< PIMAGE_NT_HEADERS >( the_module + m_base );
	m_size = m_nt_headers->OptionalHeader.SizeOfImage;

}

address module_info::find_pattern( std::string_view pattern ) {

	// returns: the address of the pattern in the module

	// size of byte array never exceeds n/2 
	// so n/2 can be used such that the array is never resized
	int* bytes = new int[ pattern.size( ) / 2 ];
	
	address result = search_byte_array( bytes, build_byte_array( pattern.data( ), bytes ) );
	
	delete[] bytes;

	return result;

}

std::size_t module_info::build_byte_array( const char* pattern, int* bytes ) {

	// n: length of pattern
	// time: O(n) 
	// space: O(n) 
	// returns: size of the byte array

	std::size_t count = 0;

	auto char_to_int = [ ]( char input ) -> int {

		if ( input >= '0' && input <= '9' )
			return input - '0';

		if ( input >= 'A' && input <= 'F' )
			return input - 'A' + 10;

		return input - 'a' + 10;

	};

	while ( pattern[ 0 ] && pattern[ 1 ] ) {

		if ( pattern[ 0 ] == '?' || pattern[ 1 ] == '?' ) {

			bytes[ count++ ] = -1;
			pattern += 1;

		} else if ( pattern[ 0 ] != ' ' && pattern[ 1 ] != ' ' ) {

			bytes[ count++ ] = char_to_int( pattern[ 0 ] ) * 16 + char_to_int( pattern[ 1 ] );

		}

		pattern += 1;

	}

	return count;

}

address module_info::search_byte_array( int* bytes, std::size_t size ) {

	// returns: the address of the byte array in the module

	address result;

	for ( std::size_t i = 0; i < m_size - size; i++ ) {

		bool found = true;
		for ( std::size_t j = 0; j < size; j++ ) {

			found = m_bitmap[ i + j ] == bytes[ j ] || bytes[ j ] == -1;
			if ( !found )
				break;

		}

		if ( !found )
			continue;

		result = &m_bitmap[ i ];
		break;

	}

	return result;

}