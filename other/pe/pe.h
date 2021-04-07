#pragma once

#include <unordered_map>

#include "../hash/hash.h"
#include "../module/module.h"

// disable cringe warning
#pragma warning(disable : 4244)

struct pe {

	// dump all present modules in peb on construct 
	// NOTE: this could cause issues if dll is loaded too early, but this is how the rest of the sdk is written
	bool setup( );

	// get export address
	std::size_t export_fn( std::size_t base, std::size_t fn_hash, bool in_memory = false );

	// get module by name
	std::size_t get( std::string_view name ) { return m_loaded_modules[ m_hash.get( name ) ]; }

private:

	// store all modules
	std::unordered_map< std::size_t, std::size_t > m_loaded_modules;

};

inline pe m_pe;