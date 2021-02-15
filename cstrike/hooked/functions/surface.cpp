#include "../hooked.h"

#include "../../render/render.h"

void __fastcall hooked::on_screen_size_changed( void* ecx, void* edx, int old_width, int old_height ) {

	static auto o_on_screen_size_changed = m_detour.get< decltype( &on_screen_size_changed ) >( "CMatSystemSurface::OnScreenSizeChanged" );

	o_on_screen_size_changed( ecx, edx, old_width, old_height );

	m_render.setup( );

}