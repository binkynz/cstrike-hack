#include "pe.h"

#include <winternl.h>
#include <TlHelp32.h>

#include "../console/console.h"

bool pe::setup( ) {

	auto peb = reinterpret_cast< _PEB* >( __readfsdword( 0x30 ) );
	if ( !peb )
		return false;

	auto list = &peb->Ldr->InMemoryOrderModuleList;
	for ( auto it = list->Flink; it != list; it = it->Flink ) {

		auto ldr_entry = CONTAINING_RECORD( it, LDR_DATA_TABLE_ENTRY, InMemoryOrderLinks );
		if ( !ldr_entry )
			continue;

		auto base_dll_name = reinterpret_cast< UNICODE_STRING* >( &ldr_entry->Reserved4[ 0 ] );

		// not a good way to do this, causes a warning as well
		// but winapi is forcing my hand
		auto wide_name = std::wstring( base_dll_name->Buffer, base_dll_name->Length >> 1 );
		auto name = std::string( wide_name.begin( ), wide_name.end( ) );

		m_loaded_modules[ m_hash.get( name ) ] = reinterpret_cast< std::size_t >( ldr_entry->DllBase );

		m_console.log( "found module %s -> 0x%x", name.data( ), m_loaded_modules[ m_hash.get( name ) ] );

	}

	return true;

}

std::size_t pe::export_fn( std::size_t base, std::size_t fn_hash, bool in_memory ) {

	auto rva_2_offset = [ ]( std::uint32_t rva, PIMAGE_NT_HEADERS nt_headers, bool in_memory = false ) {

		if ( !rva || !in_memory )
			return static_cast< std::int32_t >( rva );

		auto sec = IMAGE_FIRST_SECTION( nt_headers );
		for ( size_t i = 0; i < nt_headers->FileHeader.NumberOfSections; i++ ) {
			if ( rva >= sec->VirtualAddress && rva < sec->VirtualAddress + sec->Misc.VirtualSize )
				break;
			sec++;
		}

		return static_cast< std::int32_t >( rva - sec->VirtualAddress + sec->PointerToRawData );

	};

	auto dos_headers = reinterpret_cast< PIMAGE_DOS_HEADER >( base );
	if ( dos_headers->e_magic != IMAGE_DOS_SIGNATURE )
		return 0;

	auto nt_headers = reinterpret_cast< PIMAGE_NT_HEADERS >( base + dos_headers->e_lfanew );
	if ( nt_headers->Signature != IMAGE_NT_SIGNATURE )
		return 0;

	auto exports = reinterpret_cast< IMAGE_EXPORT_DIRECTORY* >(
		rva_2_offset( base + nt_headers->OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_EXPORT ].VirtualAddress,
			nt_headers, in_memory ) );

	auto names = reinterpret_cast< std::uint32_t* >( base + rva_2_offset( exports->AddressOfNames, nt_headers, in_memory ) );

	auto ordinal_index = static_cast< std::uint32_t >( -1 );

	// go thru all exported functions until we find our export
	for ( std::uint32_t i = 0; i < exports->NumberOfFunctions; i++ ) {

		auto function_name = reinterpret_cast< const char* >( base + rva_2_offset( names[ i ], nt_headers, in_memory ) );

		// it is what it is
		if ( m_hash.get( function_name ) == fn_hash ) {

			ordinal_index = i;
			break;

		}
	}

	if ( ordinal_index > exports->NumberOfFunctions )
		return 0;

	auto ordinals = reinterpret_cast< std::uint16_t* >( base + rva_2_offset( exports->AddressOfNameOrdinals, nt_headers, in_memory ) );
	auto addresses = reinterpret_cast< std::uint32_t* >( base + rva_2_offset( exports->AddressOfFunctions, nt_headers, in_memory ) );

	return base + rva_2_offset( addresses[ ordinals[ ordinal_index ] ], nt_headers, in_memory );

}