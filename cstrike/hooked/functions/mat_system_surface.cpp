#include "../hooked.h"

void __fastcall hooked::lock_cursor( surface* ecx, void* edx ) {

	static auto o_lock_cursor = m_detour.get< decltype( &lock_cursor ) >( "CMatSystemSurface::LockCursor" );

	if ( !m_config.m_menu_open )
		return o_lock_cursor( ecx, edx );

	ecx->unlock_cursor( );

}