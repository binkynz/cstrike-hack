#pragma once

#include <string>

#include "../cdll_int.h"
#include "../vgui/surface.h"
#include "../client_entity_list.h"
#include "../engine/debug_overlay.h"
#include "../global_vars_base.h"
#include "../tier1/localize.h"

#include "../../other/console/console.h"

struct interfaces {

	bool setup( );

	base_client_dll* m_client;
	surface* m_surface;
	client_entity_list* m_entity_list;
	debug_overlay* m_debug_overlay;
	global_vars_base* m_globals;
	engine_client* m_engine;
	localize* m_localize;

private:

	template< class t > inline t get( std::string_view module_name, std::string_view interface_name ) {

		HMODULE module = GetModuleHandleA( module_name.data( ) );

		if ( !module )
			return t( );

		auto create_interface = GetProcAddress( module, "CreateInterface" );

		if ( !create_interface )
			return t( );

		auto create_interface_fn = reinterpret_cast< t( * )( const char*, int* ) >( create_interface );

		if ( !create_interface_fn )
			return t( );

		auto interface_address = create_interface_fn( interface_name.data( ), nullptr );

		if ( !interface_address )
			return t( );

		m_console.log( "%s -> 0x%x", interface_name.data( ), interface_address );

		return interface_address;

	}

};

inline interfaces m_interfaces;