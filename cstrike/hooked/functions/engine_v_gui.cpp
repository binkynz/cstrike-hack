#include "../hooked.h"

void __fastcall hooked::paint( void* ecx, void* edx, paint_mode mode ) {

	static auto o_paint = m_detour.get< decltype( &paint ) >( "CEngineVGui::Paint" );
	
	int v3 = *( int* )ecx;

	if ( *( DWORD* )( v3 + 72 ) &&  ( mode & paint_uipanels ) != 0 ) {

		m_interfaces.m_surface->start_drawing( );

		m_visuals.paint( );

		m_interfaces.m_surface->finish_drawing( );

	}

	return o_paint( ecx, edx, mode );

}
