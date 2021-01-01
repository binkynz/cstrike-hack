#include "../hooked.h"

void __fastcall hooked::functions::paint( void* ecx, void* edx, paint_mode mode ) {

	static auto o_paint = m_paint.get< decltype( &paint ) >( );

	if ( mode & paint_uipanels ) {

		m_interfaces.m_surface->start_drawing( );

		m_visuals.paint( );

		m_interfaces.m_surface->finish_drawing( );

	}

	return o_paint( ecx, edx, mode );

}