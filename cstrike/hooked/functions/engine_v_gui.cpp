#include "../hooked.h"

void __fastcall hooked::paint( void* ecx, void* edx, paint_mode mode ) {

	static auto o_paint = m_detour.get< decltype( &paint ) >( "C_EngineVGui::Paint" );

	if ( mode & paint_uipanels ) {

		m_interfaces.m_surface->start_drawing( );

		m_visuals.paint( );

		m_interfaces.m_surface->finish_drawing( );

	}

	return o_paint( ecx, edx, mode );

}