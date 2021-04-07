#include "../hooked.h"

void __vectorcall hooked::csgo_player_anim_state_fn::update( csgo_player_anim_state* ecx, void* unk0, float z, float y, float x, void* unk1 ) {

	cs_player* player = ecx->m_player;
	if ( !player || ( !player->is_alive( ) && !player->is_player_ghost( ) ) || !ecx->cache_sequences( ) )
		return;

	x = m_mathlib_base.angle_normalize( x + player->get_third_person_recoil( ) );

	if ( ecx->m_last_update_time == m_interfaces.m_globals->m_curtime || ecx->m_last_update_frame == m_interfaces.m_globals->m_framecount )
		return;

	ecx->m_last_update_increment = std::fmaxf( 0.f, m_interfaces.m_globals->m_curtime - ecx->m_last_update_time );

	ecx->m_eye_yaw = m_mathlib_base.angle_normalize( y );
	ecx->m_eye_pitch = m_mathlib_base.angle_normalize( x );
	ecx->m_position_current = player->get_origin( );
	ecx->m_weapon = m_interfaces.m_entity_list->get< weapon_cs_base* >( player->get_active_weapon( ) );

	if ( ecx->m_weapon != ecx->m_weapon_last || ecx->m_first_run_since_init ) {

		for ( int i = 0; i < 13; i++ ) {

			animation_layer* layer = player->get_anim_overlay( i );
			if ( layer ) {

				layer->m_dispatched_studio_hdr = 0;
				layer->m_dispatched_src = -1;
				layer->m_dispatched_dst = -1;

			}

		}

	}

	ecx->m_anim_duck_amount = std::clamp( 
		m_mathlib.approach(
			std::clamp( player->get_duck_amount( ) + ecx->m_duck_additional, 0.f, 1.f ),
			ecx->m_anim_duck_amount,
			ecx->m_last_update_increment * 6.f ),
		0.f, 
		1.f );

	m_interfaces.m_mdl_cache->begin_lock( );

	player->set_sequence( 0 );
	player->get_playback_rate( ) = 0.f;

	if ( player->get_cycle( ) != 0.f ) {

		player->get_cycle( ) = 0.f;
		player->invalidate_physics_recursive( 8 );

	}

	m_interfaces.m_mdl_cache->end_lock( );

	ecx->set_up_velocity( );
	ecx->set_up_aim_matrix( );
	ecx->set_up_weapon_action( );
	ecx->set_up_movement( );
	ecx->set_up_alive_loop( );
	ecx->set_up_whole_body_action( );
	ecx->set_up_flashed_reaction( );
	ecx->set_up_flinch( );
	ecx->set_up_lean( );

	player->set_abs_angles( { 0.f, ecx->m_foot_yaw, 0.f } );

	ecx->m_weapon_last = ecx->m_weapon;
	ecx->m_position_last = ecx->m_position_current;
	ecx->m_first_run_since_init = false;
	ecx->m_last_update_time = m_interfaces.m_globals->m_curtime;
	ecx->m_last_update_frame = m_interfaces.m_globals->m_framecount;

	// compare to server hitboxes - only compare to some players to not tank fps
	if ( m_config.m_misc.server_hitboxes )
		if ( player == m_cstrike.m_local_player )
			player->draw_server_hitboxes( );

}

void __fastcall hooked::csgo_player_anim_state_fn::modify_eye_position( csgo_player_anim_state* ecx, void* edx, vector_3d& input_eye_pos ) {

	cs_player* player = ecx->m_player;
	if ( !player )
		return;

	if ( !ecx->m_landing || ecx->m_anim_duck_amount == 0.f || !player->get_ground_entity( ) )
		return;

	int head_bone = player->lookup_bone( "head_0" );
	if ( !head_bone )
		return;

	vector_3d head_pos;
	player->get_bone_position( head_bone, head_pos );

	if ( head_pos.z < input_eye_pos.z ) {

		float lerp = m_mathlib.simple_spline_remap_val_clamped( std::fabs( input_eye_pos.z - head_pos.z ), 4.f, 10.f, 0.f, 1.f );

		input_eye_pos.z = m_mathlib.lerp( lerp, input_eye_pos.z, head_pos.z );

	}

}

void __fastcall hooked::csgo_player_anim_state_fn::do_procedural_foot_plant( csgo_player_anim_state* ecx, void* edx, void* bone_to_world, void* left_foot_chain, void* right_foot_chain, void* pos ) {

	return;

}

void __fastcall hooked::csgo_player_anim_state_fn::set_up_velocity( csgo_player_anim_state* ecx, void* edx ) {

	m_interfaces.m_mdl_cache->begin_lock( );

	cs_player* player = ecx->m_player;

	vector_3d abs_velocity = player->get_abs_velocity( );

	if ( abs_velocity.length_sqr( ) > std::powf( 312.f, 2 ) )
		abs_velocity = abs_velocity.normalized( ) * 312.f;

	ecx->m_velocity_length_z = abs_velocity.z;

	abs_velocity.z = 0.f;

	ecx->m_player_is_accelerating = ( ecx->m_velocity_last.length_sqr( ) < abs_velocity.length_sqr( ) );

	ecx->m_velocity = m_mathlib.approach( abs_velocity, ecx->m_velocity, ecx->m_last_update_increment * 2000.f );
	ecx->m_velocity_normalized = ecx->m_velocity.normalized( );

	ecx->m_velocity_length_xy = std::fminf( ecx->m_velocity.length( ), 260.f );

	if ( ecx->m_velocity_length_xy > 0.f )
		ecx->m_velocity_normalized_non_zero = ecx->m_velocity_normalized;

	ecx->m_weapon = m_interfaces.m_entity_list->get< weapon_cs_base* >( player->get_active_weapon( ) );

	float max_speed_run = ecx->m_weapon ? std::fmaxf( ecx->m_weapon->get_max_speed( ), 0.001f ) : 260.f;

	ecx->m_speed_as_portion_of_run_top_speed = std::clamp( ecx->m_velocity_length_xy / max_speed_run, 0.f, 1.f );
	ecx->m_speed_as_portion_of_walk_top_speed = ecx->m_velocity_length_xy / ( max_speed_run * 0.52f );
	ecx->m_speed_as_portion_of_crouch_top_speed = ecx->m_velocity_length_xy / ( max_speed_run * 0.34f );

	if ( ecx->m_speed_as_portion_of_walk_top_speed >= 1.f )												
		ecx->m_static_approach_speed = ecx->m_velocity_length_xy;
	else if ( ecx->m_speed_as_portion_of_walk_top_speed < 0.5f )
		ecx->m_static_approach_speed = m_mathlib.approach( 80.f, ecx->m_static_approach_speed, ecx->m_last_update_increment * 60.f );

	bool started_moving_this_frame = false;
	bool stopped_moving_this_frame = false;

	if ( ecx->m_velocity_length_xy > 0.f ) {

		started_moving_this_frame = ( ecx->m_duration_moving <= 0.f );
		ecx->m_duration_still = 0.f;
		ecx->m_duration_moving += ecx->m_last_update_increment;

	} else {

		stopped_moving_this_frame = ( ecx->m_duration_still <= 0.f );
		ecx->m_duration_moving = 0.f;
		ecx->m_duration_still += ecx->m_last_update_increment;

	}

	// add server code

	ecx->m_foot_yaw_last = ecx->m_foot_yaw;
	ecx->m_foot_yaw = std::clamp( ecx->m_foot_yaw, -360.f, 360.f );

	float eye_foot_delta = m_mathlib_base.angle_diff( ecx->m_eye_yaw, ecx->m_foot_yaw );

	float aim_matrix_width_range = m_mathlib.lerp( 
		std::clamp( ecx->m_speed_as_portion_of_walk_top_speed, 0.f, 1.f ), 
		1.f,
		m_mathlib.lerp( ecx->m_walk_to_run_transition, 0.8f, 0.5f ) );

	if ( ecx->m_anim_duck_amount > 0.f )
		aim_matrix_width_range = m_mathlib.lerp( 
			ecx->m_anim_duck_amount * std::clamp( ecx->m_speed_as_portion_of_crouch_top_speed, 0.f, 1.f ), 
			aim_matrix_width_range, 
			0.5f );

	float temp_yaw_max = ecx->m_aim_yaw_max * aim_matrix_width_range;
	float temp_yaw_min = ecx->m_aim_yaw_min * aim_matrix_width_range;

	if ( eye_foot_delta > temp_yaw_max )
		ecx->m_foot_yaw = ecx->m_eye_yaw - std::fabs( temp_yaw_max );
	else if ( eye_foot_delta < temp_yaw_min )
		ecx->m_foot_yaw = ecx->m_eye_yaw + std::fabs( temp_yaw_min );

	ecx->m_foot_yaw = m_mathlib_base.angle_normalize( ecx->m_foot_yaw );

	if ( ecx->m_velocity_length_xy > 0.1f || std::fabs( ecx->m_velocity_length_z ) > 100.f ) {

		ecx->m_foot_yaw = m_mathlib_base.approach_angle( ecx->m_eye_yaw, ecx->m_foot_yaw, ecx->m_last_update_increment * ( 30.f + 20.f * ecx->m_walk_to_run_transition ) );

		ecx->m_lower_body_realign_timer = ecx->m_last_update_time + ( 1.1f * 0.2f );
		player->get_lower_body_yaw_target( ) = ecx->m_eye_yaw;

	} else {

		ecx->m_foot_yaw = m_mathlib_base.approach_angle( player->get_lower_body_yaw_target( ), ecx->m_foot_yaw, ecx->m_last_update_increment * 100.f );

		if ( ecx->m_last_update_time > ecx->m_lower_body_realign_timer
			&& std::fabsf( m_mathlib_base.angle_diff( ecx->m_foot_yaw, ecx->m_eye_yaw ) ) > 35.f ) {

			ecx->m_lower_body_realign_timer = ecx->m_last_update_time + 1.1f;
			player->get_lower_body_yaw_target( ) = ecx->m_eye_yaw;

		}

	}

	animation_layer* animation_layer_adjust = player->get_anim_overlay( 3 );
	if ( animation_layer_adjust && animation_layer_adjust->m_weight > 0.f ) {

		ecx->increment_layer_cycle( 3, false );
		ecx->increment_layer_weight( 3 );

	}

	if ( ecx->m_velocity_length_xy > 0.f ) {

		float raw_yaw_ideal = ( std::atan2( -ecx->m_velocity.y, -ecx->m_velocity.x ) * 180 / 3.141592654f );
		if ( raw_yaw_ideal < 0.f )
			raw_yaw_ideal += 360.f;

		ecx->m_move_yaw_ideal = m_mathlib_base.angle_normalize( m_mathlib_base.angle_diff( raw_yaw_ideal, ecx->m_foot_yaw ) );

	}

	ecx->m_move_yaw_current_to_ideal = m_mathlib_base.angle_normalize( m_mathlib_base.angle_diff( ecx->m_move_yaw_ideal, ecx->m_move_yaw ) );

	if ( started_moving_this_frame && ecx->m_move_weight <= 0.f ) {

		ecx->m_move_yaw = ecx->m_move_yaw_ideal;

		animation_layer* animation_layer_movement_move = player->get_anim_overlay( 6 );
		if ( animation_layer_movement_move && animation_layer_movement_move->m_sequence != -1.f ) {

			int move_sequence = animation_layer_movement_move->m_sequence;

			studio_hdr* studio_hdr = player->get_model_ptr( );
			if ( studio_hdr && studio_hdr->seqdesc( move_sequence ).numanimtags > 0 ) {

				if ( std::fabsf( m_mathlib_base.angle_diff( ecx->m_move_yaw, 180.f ) ) <= 22.5f )
					ecx->m_primary_cycle = player->get_first_sequence_anim_tag( move_sequence, 1 );
				else if ( std::fabsf( m_mathlib_base.angle_diff( ecx->m_move_yaw, 135.f ) ) <= 22.5f )
					ecx->m_primary_cycle = player->get_first_sequence_anim_tag( move_sequence, 2 );
				else if ( std::fabsf( m_mathlib_base.angle_diff( ecx->m_move_yaw, 90.f ) ) <= 22.5f )
					ecx->m_primary_cycle = player->get_first_sequence_anim_tag( move_sequence, 3 );
				else if ( std::fabsf( m_mathlib_base.angle_diff( ecx->m_move_yaw, 45.f ) ) <= 22.5f )
					ecx->m_primary_cycle = player->get_first_sequence_anim_tag( move_sequence, 4 );
				else if ( std::fabsf( m_mathlib_base.angle_diff( ecx->m_move_yaw, 0.f ) ) <= 22.5f )
					ecx->m_primary_cycle = player->get_first_sequence_anim_tag( move_sequence, 5 );
				else if ( std::fabsf( m_mathlib_base.angle_diff( ecx->m_move_yaw, -45.f ) ) <= 22.5f )
					ecx->m_primary_cycle = player->get_first_sequence_anim_tag( move_sequence, 6 );
				else if ( std::fabsf( m_mathlib_base.angle_diff( ecx->m_move_yaw, -90.f ) ) <= 22.5f )
					ecx->m_primary_cycle = player->get_first_sequence_anim_tag( move_sequence, 7 );
				else if ( std::fabsf( m_mathlib_base.angle_diff( ecx->m_move_yaw, -135.f ) ) <= 22.5f )
					ecx->m_primary_cycle = player->get_first_sequence_anim_tag( move_sequence, 8 );

			}

		}

	} else {

		animation_layer* animation_layer_movement_strafechange = player->get_anim_overlay( 7 );
		if ( animation_layer_movement_strafechange && animation_layer_movement_strafechange->m_weight >= 1.f ) {

			ecx->m_move_yaw = ecx->m_move_yaw_ideal;

		} else {

			float move_weight = m_mathlib.lerp( 
				ecx->m_anim_duck_amount,
				std::clamp( ecx->m_speed_as_portion_of_walk_top_speed, 0.f, 1.f ), 
				std::clamp( ecx->m_speed_as_portion_of_crouch_top_speed, 0.f, 1.f ) );

			float ratio = m_mathlib_base.bias( move_weight, 0.18f ) + 0.1f;

			ecx->m_move_yaw = m_mathlib_base.angle_normalize( ecx->m_move_yaw + ( ecx->m_move_yaw_current_to_ideal * ratio ) );

		}

	}

	ecx->m_pose_param_mappings[ 4 ].set_value( player, ecx->m_move_yaw );

	float aim_yaw = m_mathlib_base.angle_diff( ecx->m_eye_yaw, ecx->m_foot_yaw );
	if ( aim_yaw >= 0.f && ecx->m_aim_yaw_max != 0.f )
		aim_yaw = ( aim_yaw / ecx->m_aim_yaw_max ) * 60.f;
	else if ( ecx->m_aim_yaw_min != 0.f )
		aim_yaw = ( aim_yaw / ecx->m_aim_yaw_min ) * -60.f;

	ecx->m_pose_param_mappings[ 6 ].set_value( player, aim_yaw );

	float pitch = m_mathlib_base.angle_diff( ecx->m_eye_pitch, 0.f );
	if ( pitch > 0.f )
		pitch = ( pitch / ecx->m_aim_pitch_max ) * 90.f;
	else
		pitch = ( pitch / ecx->m_aim_pitch_min ) * -90.f;

	ecx->m_pose_param_mappings[ 7 ].set_value( player, pitch );
	ecx->m_pose_param_mappings[ 1 ].set_value( player, ecx->m_speed_as_portion_of_walk_top_speed );
	ecx->m_pose_param_mappings[ 9 ].set_value( player, 1.f - ( ecx->m_anim_duck_amount * ecx->m_in_air_smooth_value ) );

	m_interfaces.m_mdl_cache->end_lock( );

}

void __fastcall hooked::csgo_player_anim_state_fn::set_up_movement( csgo_player_anim_state* ecx, void* edx ) {

	static auto o_set_up_movement = m_modules.m_client_dll.get< decltype( &set_up_movement ) >( "CCSGOPlayerAnimState::SetUpMovement" );

	// to do

	return o_set_up_movement( ecx, edx );
}
