#include "detour.h"

#include "../signatures.h"
#include "../../other/console/console.h"
#include "../../other/pattern/pattern.h"

bool detour::setup( std::string_view name, void* function, void* custom_function ) {

	m_console.log( "%s -> 0x%x", name.data( ), function );

	if ( !function || !custom_function )
		return false;

	auto& info = m_detours[ m_hash.get( name.data( ) ) ];
	info = { function, nullptr };

	auto hook = m_signatures.m_hook.as< bool( __cdecl* )( void*, void*, void*, int ) >( );
	
	return hook( info.m_function, custom_function, &info.m_original, 0 );
}

void detour::unload( ) {

	auto restore = m_signatures.m_restore.as< void( __cdecl* )( void*, bool ) >( );

	for ( auto& detour : m_detours )
		restore( detour.second.m_function, false );

}