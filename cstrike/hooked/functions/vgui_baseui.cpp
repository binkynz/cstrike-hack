#include "../hooked.h"

#include "../../menu/menu.h"

void __fastcall hooked::vgui_baseui_fn::paint( engine_vgui* ecx, void* edx, paint_mode mode ) {

	static auto o_paint = m_modules.m_engine_dll.get< decltype( &paint ) >( "CEngineVGui::Paint" );

	if ( ecx->m_static_transition_panel && ( mode & paint_uipanels ) ) {

		m_interfaces.m_surface->start_drawing( );

		m_visuals.paint( );

		m_menu.paint( );

		m_interfaces.m_surface->finish_drawing( );

	}

	return o_paint( ecx, edx, mode );

}
