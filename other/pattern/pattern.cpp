#include "pattern.h"

#include <psapi.h>
#include <vector>

address pattern::find( std::size_t base, std::string_view pattern ) {

	static auto pattern_to_byte = [ ]( const char* pattern ) -> std::vector< std::size_t > {

		std::vector< std::size_t > bytes;

		auto start = const_cast< char* >( pattern );
		auto end = const_cast< char* >( pattern ) + std::strlen( pattern );
		for ( auto current = start; current < end; ++current ) {

			if ( *current == '?' ) {

				++current;

				if ( *current == '?' )
					++current;

				bytes.push_back( -1 );

			} else {

				bytes.push_back( std::strtoul( current, &current, 16 ) );

			}
		}

		return bytes;

	};

	auto dos_header = reinterpret_cast< PIMAGE_DOS_HEADER >( base );
	if ( dos_header->e_magic != IMAGE_DOS_SIGNATURE )
		return nullptr;

	auto nt_header = reinterpret_cast< PIMAGE_NT_HEADERS >( base + dos_header->e_lfanew );
	if ( nt_header->Signature != IMAGE_NT_SIGNATURE )
		return nullptr;

	auto image_bytes = reinterpret_cast< unsigned char* >( nt_header->OptionalHeader.ImageBase );
	if ( !image_bytes )
		return nullptr;

	auto image_size = nt_header->OptionalHeader.SizeOfImage;
	if ( !image_size )
		return nullptr;

	auto pattern_bytes = pattern_to_byte( pattern.data( ) );
	auto signature_size = pattern_bytes.size( );
	auto signature_bytes = pattern_bytes.data( );

	for ( unsigned long i = 0; i < image_size - signature_size; ++i ) {

		bool byte_sequence_found = true;

		for ( unsigned long j = 0; j < signature_size; ++j ) {

			if ( image_bytes[ i + j ] != signature_bytes[ j ] && signature_bytes[ j ] != -1 ) {

				byte_sequence_found = false;

				break;

			}
		}

		if ( byte_sequence_found )
			return &image_bytes[ i ];

	}

	return nullptr;

}