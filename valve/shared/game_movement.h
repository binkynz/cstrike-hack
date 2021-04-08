#pragma once

struct base_player;

struct move_data {



};

struct game_movement {

	inline auto process_movement( base_player* player, move_data* move ) {

		return m_utils.get_v_func< void( __thiscall* )( void*, base_player*, move_data* ) >( this, 1 )( this, player, move );

	}

	inline auto reset( ) {

		return m_utils.get_v_func< void( __thiscall* )( void* ) >( this, 2 )( this );

	}

	inline auto start_track_prediction_errors( base_player* player ) {

		return m_utils.get_v_func< void( __thiscall* )( void*, base_player* ) >( this, 3 )( this, player );

	}

	inline auto finish_track_prediction_errors( base_player* player ) {

		return m_utils.get_v_func< void( __thiscall* )( void*, base_player* ) >( this, 4 )( this, player );

	}

};