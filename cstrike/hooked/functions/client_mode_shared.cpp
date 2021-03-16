#include "../hooked.h"

bool __fastcall hooked::create_move( void* ecx, void* edx, float input_sample_time, user_cmd* cmd ) {

	m_cstrike.m_local_player = m_interfaces.m_entity_list->get< cs_player* >( m_interfaces.m_engine->get_local_player( ) );
	if ( !m_cstrike.m_local_player )
		return true;

	cmd->m_buttons |= in_bull_rush;

	return m_cstrike.m_local_player->create_move( input_sample_time, cmd );

}

float __fastcall hooked::get_view_model_fov( void* ecx, void* edx ) {

	return 95.f;

}