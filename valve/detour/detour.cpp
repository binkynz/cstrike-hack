#include "detour.h"

#include "../../other/pattern/pattern.h"

bool detour::hook( void* function, void* detour_function ) {

	m_normal = function;

	if ( !m_normal || !detour_function )
		return false;

	const auto hook_fn = m_pattern.find( "gameoverlayrenderer.dll", "55 8B EC 51 8B 45 10 C7" ).as< bool( __cdecl* )( void*, void*, void*, int ) >( );

	if ( !hook_fn )
		return false;

	return hook_fn( m_normal, detour_function, &m_original, 0 );

}

void detour::unload( ) {

	const auto unload_fn = m_pattern.find( "gameoverlayrenderer.dll", "E8 ? ? ? ? 83 C4 08 FF 15 ? ? ? ?" ).relative( ).as< void( __cdecl* )( void*, bool ) >( );

	unload_fn( m_normal, false );

}