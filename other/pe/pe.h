#pragma once

#include "../console/console.h"
#include "../hash/hash.h"

#include <Windows.h>
#include <intrin.h>
#include <winternl.h>
#include <TlHelp32.h>

#include <unordered_map>

// disable cringe warning
#pragma warning(disable : 4244)

struct pe {
	// store all modules
	std::unordered_map<std::size_t , std::uintptr_t> m_loaded_modules;

	// dump all present modules in peb on construct 
	// NOTE: this could cause issues if dll is loaded too early, but this is how the rest of the sdk is written
	bool setup ( ) {
		const auto peb = reinterpret_cast< _PEB * >( __readfsdword ( 0x30 ) );
		if ( !peb )
			return false;

		const auto list = &peb->Ldr->InMemoryOrderModuleList;

		for ( auto it = list->Flink; it != list; it = it->Flink ) {
			const auto ldr_entry = CONTAINING_RECORD ( it , LDR_DATA_TABLE_ENTRY , InMemoryOrderLinks );
			if ( !ldr_entry )
				continue;

			const auto base_dll_name = reinterpret_cast< UNICODE_STRING * >( &ldr_entry->Reserved4 [ 0 ] );

			// not a good way to do this, causes a warning as well
			// but winapi is forcing my hand
			const auto wide_name = std::wstring ( base_dll_name->Buffer , base_dll_name->Length >> 1 );
			const auto name = std::string ( wide_name.begin ( ) , wide_name.end ( ) );

			this->m_loaded_modules [ m_hash.get ( name ) ] = reinterpret_cast< std::uintptr_t >( ldr_entry->DllBase );

			m_console.log ( "found module %s -> 0x%x" , name.data ( ) , this->m_loaded_modules [ m_hash.get ( name ) ] );
		}

		return true;
	}

	// get module base by hash
	std::uintptr_t get ( std::size_t hash ) {
		return this->m_loaded_modules [ hash ];
	}

	// get export address
	std::uintptr_t export_fn ( const std::uintptr_t base , const std::size_t fn_hash , const bool in_memory = false ) {
		const auto rva_2_offset = [ ] ( const std::uint32_t rva , PIMAGE_NT_HEADERS nt_headers , const bool in_memory = false ) {
			if ( !rva || !in_memory )
				return static_cast< std::int32_t >( rva );

			auto sec = IMAGE_FIRST_SECTION ( nt_headers );
			for ( size_t i = 0; i < nt_headers->FileHeader.NumberOfSections; i++ ) {
				if ( rva >= sec->VirtualAddress && rva < sec->VirtualAddress + sec->Misc.VirtualSize )
					break;
				sec++;
			}

			return static_cast< std::int32_t >( rva - sec->VirtualAddress + sec->PointerToRawData );
		};

		const auto dos_headers = reinterpret_cast< PIMAGE_DOS_HEADER >( base );
		if ( dos_headers->e_magic != IMAGE_DOS_SIGNATURE )
			return 0;

		const auto nt_headers = reinterpret_cast< PIMAGE_NT_HEADERS >( base + dos_headers->e_lfanew );
		if ( nt_headers->Signature != IMAGE_NT_SIGNATURE )
			return 0;

		const auto exports = reinterpret_cast< IMAGE_EXPORT_DIRECTORY * >(
			rva_2_offset ( base + nt_headers->OptionalHeader.DataDirectory [ IMAGE_DIRECTORY_ENTRY_EXPORT ].VirtualAddress ,
			nt_headers , in_memory ) );

		const auto names = reinterpret_cast< std::uint32_t * >( base + rva_2_offset ( exports->AddressOfNames , nt_headers , in_memory ) );

		auto ordinal_index = static_cast< std::uint32_t >( -1 );
		
		// go thru all exported functions until we find our export
		for ( std::uint32_t i = 0; i < exports->NumberOfFunctions; i++ ) {
			const auto function_name = reinterpret_cast< const char * >( base + rva_2_offset ( names [ i ] , nt_headers , in_memory ) );

			// it is what it is
			if ( m_hash.get ( function_name ) == fn_hash ) {
				ordinal_index = i;
				break;
			}
		}

		if ( ordinal_index > exports->NumberOfFunctions )
			return 0;

		const auto ordinals = reinterpret_cast< std::uint16_t * >( base + rva_2_offset ( exports->AddressOfNameOrdinals , nt_headers , in_memory ) );
		const auto addresses = reinterpret_cast< std::uint32_t * >( base + rva_2_offset ( exports->AddressOfFunctions , nt_headers , in_memory ) );
		return base + rva_2_offset ( addresses [ ordinals [ ordinal_index ] ] , nt_headers , in_memory );
	}
};

inline pe m_pe {};