#pragma once

#include <functional>
#include <unordered_map>
#include <vector>

#include "../../other/hash/hash.h"

struct detour {

	bool setup( std::string_view name, void* function, void* custom_function );

	void unload( );

	template< typename t > inline t get( std::string_view name ) {

		return ( t )m_detours[ m_hash.get( name.data( ) ) ].m_original;

	}

private:

	struct m_info {

		void* m_function;

		void* m_original;

	};

	std::unordered_map< std::size_t, m_info > m_detours;

};

inline detour m_detour;