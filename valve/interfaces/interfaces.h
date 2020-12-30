#pragma once

#include <string>

#include "../cdll_int.h"

#include "../../other/console/console.h"

struct interfaces {

	bool setup( );

	base_client_dll* m_client;

private:

	template< class t > inline t get( const std::string_view module_name, const std::string_view interface_name ) {

		const auto module = GetModuleHandleA( module_name.data( ) );

		if ( !module )
			return t( );

		const auto create_interface = GetProcAddress( module, "CreateInterface" );

		if ( !create_interface )
			return t( );

		const auto create_interface_fn = reinterpret_cast< t( * )( const char*, int* ) >( create_interface );

		if ( !create_interface_fn )
			return t( );

		const auto interface_address = create_interface_fn( interface_name.data( ), nullptr );

		if ( !interface_address )
			return t( );

		m_console.log( "%s -> 0x%x", interface_name.data( ), interface_address );

		return interface_address;

	}

};

inline interfaces m_interfaces;