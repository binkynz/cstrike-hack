#include "interfaces.h"

bool interfaces::setup( ) {

	m_console.log( "grabbing interfaces..." );

	m_client = get< base_client_dll* >( "client.dll", "VClient018" );
	if ( !m_client )
		return false;

	m_surface = get< surface* >( "vguimatsurface.dll", "VGUI_Surface031" );
	if ( !m_surface )
		return false;

	m_entity_list = get< client_entity_list* >( "client.dll", "VClientEntityList003" );
	if ( !m_entity_list )
		return false;

	m_debug_overlay = get< debug_overlay* >( "engine.dll", "VDebugOverlay004" );
	if ( !m_debug_overlay )
		return false;

	m_globals = m_utils.get_v_func( m_client, 11 ).add( 0xa ).get< global_vars_base* >( 2 );
	if ( !m_globals )
		return false;

	m_console.log( "gpGlobals -> 0x%x", m_globals );
	m_engine = get< engine_client* >( "engine.dll", "VEngineClient014" );
	if ( !m_engine )
		return false;

	m_localize = get< localize* >( "localize.dll", "Localize_001" );
	if ( !m_localize )
		return false;

	m_mdl_cache = get< mdl_cache* >( "datacache.dll", "MDLCache004" );
	if ( !m_mdl_cache )
		return false;

	m_console.log( "grabbed interfaces" );

	return true;

}