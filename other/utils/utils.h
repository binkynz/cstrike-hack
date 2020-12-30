#pragma once

#include <windows.h>
#include <thread>
#include <cstddef>

struct utils {

	bool create_thread( DWORD WINAPI function( void* ), void* parameter );

	inline void sleep( const std::size_t& milliseconds ) {

		std::this_thread::sleep_for( std::chrono::milliseconds( milliseconds ) );

	}

};

inline utils m_utils;