#pragma once

#include <windows.h>
#include <cstddef>
#include <cstdint>
#include <string>

#include "../memory/address.h"

struct module_info {

	module_info( ) = default;

	module_info( std::size_t the_module );

	address find_pattern( std::string_view pattern );

	std::size_t get_module( ) { return m_module; }

private:

	std::size_t build_byte_array( const char* pattern, int* bytes );
	address search_byte_array( int* bytes, std::size_t size );

	std::size_t m_module;
	std::uint8_t* m_bitmap;
	PIMAGE_DOS_HEADER m_dos_header;
	std::uint64_t m_base;
	PIMAGE_NT_HEADERS m_nt_headers;
	std::uint64_t m_size;

};