#pragma once

#include <windows.h>
#include <thread>
#include <cstddef>

#include "../memory/address.h"

struct utils {

	bool create_thread( DWORD WINAPI function( void* ), void* parameter );

	inline void sleep( const std::size_t& milliseconds ) {

		std::this_thread::sleep_for( std::chrono::milliseconds( milliseconds ) );

	}

	template< typename t = address > inline t get_v_func( const address pointer, const std::size_t& index ) {

		return ( t )( pointer.to< t* >( )[ index ] );

	}

};

inline utils m_utils;