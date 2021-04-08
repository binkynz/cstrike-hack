#include "../hooked.h"

void __fastcall hooked::prediction_fn::run_command( prediction* ecx, void* edx, base_player* player, user_cmd* cmd, move_helper* move_helper ) {

	ecx->start_command( player, cmd );

	m_interfaces.m_globals->m_curtime = player->get_tick_base( ) * m_interfaces.m_globals->m_interval_per_tick;
	m_interfaces.m_globals->m_frametime = ecx->m_engine_paused ? 0.f : m_interfaces.m_globals->m_interval_per_tick;

	cmd->m_buttons |= player->get_button_forced( );
	cmd->m_buttons &= ~player->get_button_disabled( );

	m_interfaces.m_game_movement->start_track_prediction_errors( player );

	if ( cmd->m_weapon_select != 0 ) {

		weapon_cs_base* weapon = m_interfaces.m_entity_list->get< weapon_cs_base* >( cmd->m_weapon_select );
		if ( weapon ) {

			cs_weapon_info* weapon_info = weapon->get_cs_wpn_data( );
			if ( weapon_info )
				player->select_item( weapon_info->m_weapon_name, cmd->m_weapon_sub_type );

		}

	}

	// no vehicles around here
	
	if ( cmd->m_impulse )
		player->get_impulse( ) = cmd->m_impulse;

	player->update_button_state( cmd->m_buttons );

	ecx->check_moving_ground( player, m_interfaces.m_globals->m_frametime );

	player->set_local_view_angles( cmd->m_view_angles );

	ecx->run_pre_think( player );

	ecx->run_think( player, m_interfaces.m_globals->m_interval_per_tick );

	ecx->setup_move( player, cmd, move_helper, m_interfaces.m_move_data );

	// still no vehicles ;?

	m_interfaces.m_game_movement->process_movement( player, m_interfaces.m_move_data );

	ecx->finish_move( player, cmd, m_interfaces.m_move_data );

	move_helper->process_impacts( );

	ecx->run_post_think( player );

	m_interfaces.m_game_movement->finish_track_prediction_errors( player );

	ecx->finish_command( player );

	m_interfaces.m_game_movement->reset( );

	if ( !ecx->m_engine_paused && m_interfaces.m_globals->m_frametime > 0.f )
		player->get_tick_base( )++;

}
