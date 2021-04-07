#include "../hooked.h"

#include "../../render/render.h"

void __fastcall hooked::scheme_manager_fn::reload_schemes( void* ecx, void* edx ) {

	static auto o_reload_schemes = m_modules.m_vgui2_dll.get< decltype( &reload_schemes ) >( "CSchemeManager::ReloadSchemes" );

	o_reload_schemes( ecx, edx );

	m_render.setup( );

}