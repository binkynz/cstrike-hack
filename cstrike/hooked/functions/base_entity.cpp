#include "../hooked.h"

bool __fastcall hooked::should_interpolate( base_entity* ecx, void* edx ) {

	static auto o_should_interpolate = m_detour.get< decltype( &should_interpolate ) >( "C_BaseEntity::ShouldInterpolate" );

	if ( ecx->is_player( ) )
		return false;

	return o_should_interpolate( ecx, edx );

}