#include "pattern.h"

#include <psapi.h>
#include <vector>

address pattern::find( std::string_view module_name, std::string_view pattern ) {

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

	HMODULE handle = GetModuleHandleA( module_name.data( ) );
	if ( !handle )
		return nullptr;

	MODULEINFO module_info;
	if ( !K32GetModuleInformation( GetCurrentProcess( ), handle, &module_info, sizeof( MODULEINFO ) ) )
		return nullptr;

	auto image_bytes = reinterpret_cast< unsigned char* >( handle );
	if ( !image_bytes )
		return nullptr;

	auto image_size = module_info.SizeOfImage;
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