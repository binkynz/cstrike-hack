#pragma once

#include "../other/pattern/pattern.h"

struct signatures {

	// offsets

	address m_anim_overlay = m_pattern.find( "client.dll", "8B 80 ? ? ? ? 03 C1 74 15" );
	address m_abs_velocity = m_pattern.find( "client.dll", "F3 0F 10 A6 ? ? ? ? F3 0F 11 64 24 ?" );

	// functions

	address m_create_move = m_pattern.find( "client.dll", "E8 ? ? ? ? FF 15 ? ? ? ? 84 C0 74 29" ).relative( );
	address m_paint = m_pattern.find( "engine.dll", "55 8B EC 83 EC 40 53 8B D9 8B 0D ? ? ? ? 89 5D F8" );
	address m_get_view_model_fov = m_pattern.find( "client.dll", "55 8B EC 8B 0D ? ? ? ? 83 EC 08 57" );
	address m_draw_crosshair = m_pattern.find( "client.dll", "55 8B EC 83 E4 F0 83 EC 78 56 8B F1 8B 0D ? ? ? ?" );
	address m_update = m_pattern.find( "client.dll", "E8 ? ? ? ? E9 ? ? ? ? 83 BE ? ? ? ? ?" ).relative( );
	address m_modify_eye_position = m_pattern.find( "client.dll", "E8 ? ? ? ? 8B 06 8B CE FF 90 ? ? ? ? 85 C0 74 50" ).relative( );
	address m_do_procedural_foot_plant = m_pattern.find( "client.dll", "E8 ? ? ? ? F6 86 ? ? ? ? ? 0F 84 ? ? ? ?" ).relative( );
	address m_setup_velocity = m_pattern.find( "client.dll", "55 8B EC 83 E4 F8 83 EC 30 56 57 8B 3D ? ? ? ?" );
	address m_setup_movement = m_pattern.find( "client.dll", "E8 ? ? ? ? 8B CF E8 ? ? ? ? 8B CF E8 ? ? ? ? 8B 47 60" ).relative( );
	address m_setup_aim_matrix = m_pattern.find( "client.dll", "55 8B EC 81 EC ? ? ? ? 53 56 57 8B 3D ? ? ? ?" );
	address m_set_up_weapon_action = m_pattern.find( "client.dll", "55 8B EC 51 53 56 57 8B F9 8B 77 60" );
	address m_set_up_movement = m_pattern.find( "client.dll", "E8 ? ? ? ? 8B CF E8 ? ? ? ? 8B CF E8 ? ? ? ? 8B 47 60" ).relative( );
	address m_set_up_alive_loop = m_pattern.find( "client.dll", "E8 ? ? ? ? 8B CF E8 ? ? ? ? 8B 47 60" ).relative( );
	address m_set_up_whole_body_action = m_pattern.find( "client.dll", "E8 ? ? ? ? 8B 47 60 83 B8 ? ? ? ? ?" ).relative( );
	address m_set_up_flinch = m_pattern.find( "client.dll", "E8 ? ? ? ? 8B CF E8 ? ? ? ? 33 C0" ).relative( );
	address m_set_up_lean = m_pattern.find( "client.dll", "E8 ? ? ? ? 33 C0 89 44 24 0C" ).relative( );
	address m_cache_sequences = m_pattern.find( "client.dll", "E8 ? ? ? ? 84 C0 0F 84 ? ? ? ? 8B 77 60" ).relative( );
	address m_get_ground_entity = m_pattern.find( "client.dll", "E8 ? ? ? ? 8B 4C 24 14 85 C0" ).relative( );
	address m_invalidate_physics_recursive = m_pattern.find( "client.dll", "E8 ? ? ? ? 89 5E 18" ).relative( );
	address m_set_abs_angles = m_pattern.find( "client.dll", "E8 ? ? ? ? 53 8D 45 F0" ).relative( );
	address m_lookup_bone = m_pattern.find( "client.dll", "E8 ? ? ? ? 89 44 24 5C" ).relative( );
	address m_get_bone_position = m_pattern.find( "client.dll", "E8 ? ? ? ? 8D 14 24" ).relative( );
	address m_calc_absolute_velocity = m_pattern.find( "client.dll", "E8 ? ? ? ? 83 7B 30 00" ).relative( );
	address m_increment_layer_cycle = m_pattern.find( "client.dll", "E8 ? ? ? ? FF 76 60 F3 0F 10 54 24 ?" ).relative( );
	address m_increment_layer_weight = m_pattern.find( "client.dll", "E8 ? ? ? ? 8B 5F 60 83 BB ? ? ? ? ?" ).relative( );
	address m_get_model_ptr = m_pattern.find( "client.dll", "E8 ? ? ? ? 8B 55 38" ).relative( );
	address m_get_first_sequence_anim_tag = m_pattern.find( "client.dll", "E8 ? ? ? ? F3 0F 11 86 ? ? ? ? 0F 57 DB" ).relative( );
	address m_seqdesc = m_pattern.find( "client.dll", "E8 ? ? ? ? 03 40 04" ).relative( );
	address m_lookup_pose_parameter = m_pattern.find( "client.dll", "E8 ? ? ? ? 85 C0 79 08" ).relative( );
	address m_studio_set_pose_parameter = m_pattern.find( "client.dll", "E8 ? ? ? ? 0F 28 D8 83 C4 04" ).relative( );
	address m_cam_think = m_pattern.find( "client.dll", "55 8B EC 83 E4 F8 81 EC ? ? ? ? 56 8B F1 8B 0D ? ? ? ? 57 85 C9" );
	address m_cam_to_third_person = m_pattern.find( "client.dll", "55 8B EC 83 EC 0C 8D 55 F4" );
	address m_add_renderable = m_pattern.find( "client.dll", "55 8B EC 56 8B 75 08 57 FF 75 18" );

	address m_list_leaves_in_box = m_pattern.find( "engine.dll", "55 8B EC 83 EC 18 8B 4D 0C" );

	address m_start_drawing = m_pattern.find( "vguimatsurface.dll", "55 8B EC 83 E4 C0 83 EC 38" );
	address m_finish_drawing = m_pattern.find( "vguimatsurface.dll", "8B 0D ? ? ? ? 56 C6 05 ? ? ? ? ?" );

	address m_reload_schemes = m_pattern.find( "vgui2.dll", "55 8B EC 83 EC 08 53 56 8B F1 6A 00" );

	address m_draw_model = m_pattern.find( "studiorender.dll", "55 8B EC 83 E4 F8 83 EC 54" );

	address m_hook = m_pattern.find( "gameoverlayrenderer.dll", "55 8B EC 51 8B 45 10 C7" );
	address m_restore = m_pattern.find( "gameoverlayrenderer.dll", "E8 ? ? ? ? 83 C4 08 FF 15 ? ? ? ?" ).relative( );

	address m_draw_server_hitboxes = m_pattern.find( "server.dll", "E8 ? ? ? ? F6 83 ? ? ? ? ? 0F 84 ? ? ? ? 33 FF" ).relative( );
	address m_util_player_by_index = m_pattern.find( "server.dll", "85 C9 7E 2A A1 ? ? ? ?" );

};

inline signatures m_signatures;