#include "interfaces.h"

bool interfaces::setup( ) {

	m_client = get< base_client_dll* >( m_modules.m_client_dll, "VClient" );
	if ( !m_client )
		return false;

	m_surface = get< surface* >( m_modules.m_vguimatsurface_dll, "VGUI_Surface" );
	if ( !m_surface )
		return false;

	m_entity_list = get< client_entity_list* >( m_modules.m_client_dll, "VClientEntityList" );
	if ( !m_entity_list )
		return false;

	m_debug_overlay = get< debug_overlay* >( m_modules.m_engine_dll, "VDebugOverlay" );
	if ( !m_debug_overlay )
		return false;

	m_globals = m_utils.get_v_func( m_client, 11 ).add( 0xa ).get< global_vars_base* >( 2 );
	if ( !m_globals )
		return false;

	m_console.log( "found pointer gpGlobals -> 0x%x", m_globals );

	m_engine = get< engine_client* >( m_modules.m_engine_dll, "VEngineClient" );
	if ( !m_engine )
		return false;

	m_localize = get< localize* >( m_modules.m_localize_dll, "Localize_" );
	if ( !m_localize )
		return false;

	m_mdl_cache = get< mdl_cache* >( m_modules.m_datacache_dll, "MDLCache" );
	if ( !m_mdl_cache )
		return false;

	m_material_system = get< material_system* >( m_modules.m_materialsystem_dll, "VMaterialSystem" );
	if ( !m_material_system )
		return false;

	m_net_graph_panel = m_modules.m_client_dll.get_address( "g_pNetGraphPanel" ).add( 0x2 ).get< net_graph_panel* >( 2 );
	if ( !m_net_graph_panel )
		return false;

	m_console.log( "found pointer g_pNetGraphPanel -> 0x%x", m_net_graph_panel );

	m_client_state = m_utils.get_v_func( m_engine, 12 ).add( 0x10 ).get< client_state* >( 2 );
	if ( !m_client_state )
		return false;

	m_console.log( "found reference to GetBaseLocalClient -> 0x%x", m_client_state );

	m_mem_alloc = *reinterpret_cast< mem_alloc** >( m_pe.export_fn( m_modules.m_tier0.get_module( ), m_hash.get( "g_pMemAlloc" ) ) );
	if ( !m_mem_alloc )
		return false;

	m_console.log( "found pointer g_pMemAlloc -> 0x%x", m_mem_alloc );

	return true;

}