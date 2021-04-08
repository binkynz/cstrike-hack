#pragma once

#include "../shared/user_cmd.h"

struct base_player;
struct move_helper;
struct move_data;

struct prediction {

	inline auto check_moving_ground( base_player* player, double frametime ) {

		return m_utils.get_v_func< void( __thiscall* )( void*, base_player*, double ) >( this, 18 )( this, player, frametime );

	}

	inline auto setup_move( base_player* player, user_cmd* cmd, move_helper* helper, move_data* move ) {

		return m_utils.get_v_func< void( __thiscall* )( void*, base_player*, user_cmd*, move_helper*, move_data* ) >( this, 20 )( this, player, cmd, helper, move );

	}

	inline auto finish_move( base_player* player, user_cmd* cmd, move_data* move ) {

		return m_utils.get_v_func< void( __thiscall* )( void*, base_player*, user_cmd*, move_data* ) >( this, 21 )( this, player, cmd, move );

	}

	inline auto start_command( base_player* player, user_cmd* cmd ) {

		player->get_current_command( ) = cmd;
		player->get_last_command( ) = *cmd;
		base_entity::set_prediction_random_seed( cmd );
		base_entity::set_prediction_player( player );

	}

	inline auto run_pre_think( base_player* player ) {

		if ( !player->physics_run_think( ) )
			return;

		player->pre_think( );

	}

	inline auto run_think( base_player* player, double frametime ) {

		int thinktick = player->get_next_think_tick( );

		if ( thinktick <= 0 || thinktick > player->get_tick_base( ) )
			return;

		{ /* C_BaseEntity::SetNextThink */
			player->get_next_think_tick( ) = -1;

			player->check_has_think_function( false );
		}

		player->think( );

	}

	inline auto run_post_think( base_player* player ) {

		player->post_think( );

	}

	inline auto finish_command( base_player* player ) {

		player->get_current_command( ) = 0;
		base_entity::set_prediction_random_seed( 0 );
		base_entity::set_prediction_player( 0 );

	}

	char _pad0[ 0xa ]; // 0
	bool m_engine_paused; // 10

};