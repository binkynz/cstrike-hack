#pragma once

#include <windows.h>
#include <cstddef>
#include <cstdint>
#include <string>
#include <unordered_map>

#include "../memory/address.h"
#include "../hash/hash.h"

struct module_info {

	module_info( ) = default;

	module_info( std::size_t loaded_module );

	std::size_t get_module( ) { return m_loaded_module; }

protected:

	std::size_t m_loaded_module;
	std::uint8_t* m_bitmap;
	PIMAGE_DOS_HEADER m_dos_header;
	long m_base;
	PIMAGE_NT_HEADERS m_nt_headers;
	unsigned long m_size;

};

struct pattern : public module_info {

	pattern( ) = default;

	pattern( std::size_t loaded_module ) : module_info( loaded_module ) { };

	address find( std::string_view pattern );

private:

	std::size_t build_byte_array( const char* pattern, int* bytes );
	address search_byte_array( int* bytes, std::size_t size );

};

struct detour {

	virtual bool hook_function( std::string_view name, void* custom_function ) = 0;

	virtual void unload_functions( ) = 0;

	template< typename t > inline t get( std::string_view name ) { return ( t )m_originals[ m_hash.get( name ) ]; }

protected:

	std::unordered_map< std::size_t, void* > m_originals;

};

struct loaded_module : public pattern, detour {

	loaded_module( ) = default;

	loaded_module( std::size_t loaded_module ) : pattern( loaded_module ) { };

	bool add_address( std::string_view name, std::string_view pattern, bool relative = false );

	bool hook_function( std::string_view name, void* custom_function );

	void unload_functions( );

	address get_address( std::string_view name ) { return m_addresses[ m_hash.get( name ) ]; }

	bool valid_addresses( );

private:

	std::unordered_map< std::size_t, address > m_addresses;

};