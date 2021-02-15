#include "../hooked.h"

#include "../../render/render.h"

void __fastcall hooked::reload_schemes( void* ecx, void* edx ) {

	static auto o_reload_schemes = m_detour.get< decltype( &reload_schemes ) >( "CSchemeManager::ReloadSchemes" );

	o_reload_schemes( ecx, edx );

	m_render.setup( );

}