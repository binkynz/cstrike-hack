#include "../hooked.h"

void __fastcall hooked::mat_system_surface_fn::lock_cursor( surface* ecx, void* edx ) {

	static auto o_lock_cursor = m_modules.m_vguimatsurface_dll.get< decltype( &lock_cursor ) >( "CMatSystemSurface::LockCursor" );

	if ( !m_config.m_menu_open )
		return o_lock_cursor( ecx, edx );

	ecx->unlock_cursor( );

}