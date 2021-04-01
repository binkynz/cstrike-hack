#pragma once

struct animstate_pose_param_cache {

	bool m_initialized; // 0
	char _pad0[ 0x3 ]; // 1
	int m_index; // 4
	const char* m_name; // 8

	inline bool init( cs_player* player, const char* pose_param_name ) {

		m_interfaces.m_mdl_cache->begin_lock( );

		m_name = pose_param_name;
		m_index = player->lookup_pose_parameter( pose_param_name );

		if ( m_index != 1 )
			m_initialized = true;

		m_interfaces.m_mdl_cache->end_lock( );

		return m_initialized;

	}

	inline void set_value( cs_player* player, float value ) {

		if ( !m_initialized )
			init( player, m_name );

		if ( m_initialized && player ) {

			m_interfaces.m_mdl_cache->begin_lock( );

			player->set_pose_parameter( m_index, value );

			m_interfaces.m_mdl_cache->end_lock( );

		}

	}

}; // size: 12

struct csgo_player_anim_state {

	inline auto set_up_velocity( ) {

		auto function = m_signatures.m_setup_velocity.as< void( __thiscall* )( void* ) >( );

		return function( this );

	}

	inline auto set_up_aim_matrix( ) {

		auto function = m_signatures.m_setup_aim_matrix.as< void( __thiscall* )( void* ) >( );

		return function( this );

	}

	inline auto set_up_weapon_action( ) {

		auto function = m_signatures.m_set_up_weapon_action.as< void( __thiscall* )( void* ) >( );

		return function( this );

	}

	inline auto set_up_movement( ) {

		auto function = m_signatures.m_set_up_movement.as< void( __thiscall* )( void* ) >( );

		return function( this );

	}

	inline auto set_up_alive_loop( ) {

		auto function = m_signatures.m_set_up_alive_loop.as< void( __thiscall* )( void* ) >( );

		return function( this );

	}

	inline auto set_up_whole_body_action( ) {

		auto function = m_signatures.m_set_up_whole_body_action.as< void( __thiscall* )( void* ) >( );

		return function( this );

	}

	inline auto set_up_flashed_reaction( ) {

		// to do

	}

	inline auto set_up_flinch( ) {

		auto function = m_signatures.m_set_up_flinch.as< void( __thiscall* )( void* ) >( );

		return function( this );

	}

	inline auto set_up_lean( ) {

		auto function = m_signatures.m_set_up_lean.as< void( __thiscall* )( void* ) >( );

		return function( this );

	}

	inline auto cache_sequences( ) {

		auto function = m_signatures.m_cache_sequences.as< bool( __thiscall* )( void* ) >( );

		return function( this );

	}

	inline auto increment_layer_cycle( int layer_index, bool allow_loop ) {

		auto function = m_signatures.m_increment_layer_cycle.as< void( __thiscall* )( void*, int, bool ) >( );

		return function( this, layer_index, allow_loop );

	}

	inline auto increment_layer_weight( int layer_index ) {

		auto function = m_signatures.m_increment_layer_weight.as< void( __thiscall* )( void*, int ) >( );

		return function( this, layer_index );

	}

	char _pad0[ 0x4 ]; // 0
	bool m_first_run_since_init; // 4
	char _pad1[ 0x5b ]; // 5
	cs_player* m_player; // 96
	weapon_cs_base* m_weapon; // 100
	weapon_cs_base* m_weapon_last; // 104
	float m_last_update_time; // 108
	int m_last_update_frame; // 112
	float m_last_update_increment; // 116
	float m_eye_yaw; // 120
	float m_eye_pitch; // 124
	float m_foot_yaw; // 128
	float m_foot_yaw_last; // 132
	float m_move_yaw; // 136
	float m_move_yaw_ideal; // 140
	float m_move_yaw_current_to_ideal; // 144
	float m_time_to_align_lower_body; // 148
	float m_primary_cycle; // 152
	float m_move_weight; // 156
	float m_move_weight_smoothed; // 160
	float m_anim_duck_amount; // 164
	float m_duck_additional; // 168
	float m_recrouch_weight; // 172
	vector_3d m_position_current; // 176
	vector_3d m_position_last; // 188
	vector_3d m_velocity; // 200
	vector_3d m_velocity_normalized; // 212
	vector_3d m_velocity_normalized_non_zero; // 224
	float m_velocity_length_xy; // 236
	float m_velocity_length_z; // 240
	float m_speed_as_portion_of_run_top_speed; // 244
	float m_speed_as_portion_of_walk_top_speed; // 248
	float m_speed_as_portion_of_crouch_top_speed; // 252
	float m_duration_moving; // 256
	float m_duration_still; // 260
	bool m_on_ground; // 264
	bool m_landing; // 265
	char _pad2[ 0x12 ]; // 266
	float m_walk_to_run_transition; // 284
	char _pad3[ 0x4 ]; // 288
	float m_in_air_smooth_value; // 292
	bool m_on_ladder; // 296
	char _pad4[ 0x3 ]; // 297
	float m_ladder_weight; // 300
	char _pad5[ 0x2c ]; // 304
	vector_3d m_velocity_last; // 348
	char _pad6[ 0x45 ]; // 360
	bool m_player_is_accelerating; // 429
	char _pad7[ 0x2 ]; // 430
	animstate_pose_param_cache m_pose_param_mappings[ 20 ]; // 432
	float m_duration_move_weight_is_too_high; // 672
	float m_static_approach_speed; // 676
	int m_previous_move_state; // 680
	float m_stutter_step; // 684
	char _pad8[ 0x80 ]; // 688
	float m_aim_yaw_min; // 816
	float m_aim_yaw_max; // 820
	float m_aim_pitch_min; // 824
	float m_aim_pitch_max; // 828

	// custom members
	float m_lower_body_realign_timer;

};