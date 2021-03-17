#pragma once

#include <windows.h>
#include <unordered_map>

// disable cringe warning
#pragma warning(disable : 4244)

struct pe {

	// dump all present modules in peb on construct 
	// NOTE: this could cause issues if dll is loaded too early, but this is how the rest of the sdk is written
	bool setup( );

	// get export address
	std::size_t export_fn( std::size_t base, std::size_t fn_hash, bool in_memory = false );

	// get module base by hash
	std::size_t get( std::size_t hash ) {

		return m_loaded_modules[ hash ];

	}

private:

	// store all modules
	std::unordered_map< std::size_t, std::size_t > m_loaded_modules;

};

inline pe m_pe;