#include "signatures.h"

#include "../../other/hash/hash.h"
#include "../../other/pe/pe.h"

bool signatures::setup( ) {

	// module names

	m_client_dll = m_pe.get( m_hash.get( "client.dll" ) );
	m_engine_dll = m_pe.get( m_hash.get( "engine.dll" ) );
	m_server_dll = m_pe.get( m_hash.get( "server.dll" ) );
	m_gameoverlayrenderer_dll = m_pe.get( m_hash.get( "gameoverlayrenderer.dll" ) );
	m_vgui2_dll = m_pe.get( m_hash.get( "vgui2.dll" ) );
	m_vguimatsurface_dll = m_pe.get( m_hash.get( "vguimatsurface.dll" ) );
	m_studiorender_dll = m_pe.get( m_hash.get( "studiorender.dll" ) );
	m_localize_dll = m_pe.get( m_hash.get( "localize.dll" ) );
	m_datacache_dll = m_pe.get( m_hash.get( "datacache.dll" ) );
	m_materialsystem_dll = m_pe.get( m_hash.get( "materialsystem.dll" ) );

	// offsets

	m_anim_overlay = m_pattern.find( m_client_dll, "8B 80 ? ? ? ? 03 C1 74 15" );
	m_abs_velocity = m_pattern.find( m_client_dll, "F3 0F 10 A6 ? ? ? ? F3 0F 11 64 24 ?" );
	m_player_anim_state_csgo = m_pattern.find( m_client_dll, "8B 8E ? ? ? ? EB 39" );

	// functions

	m_level_shutdown = m_pattern.find( m_client_dll, "55 8B EC 83 E4 F8 83 EC 30 C6 05 ? ? ? ? ?" );
	m_create_move = m_pattern.find( m_client_dll, "55 8B EC 8B 0D ? ? ? ? 85 C9 75 06" );
	m_get_view_model_fov = m_pattern.find( m_client_dll, "55 8B EC 8B 0D ? ? ? ? 83 EC 08 57" );
	m_paint = m_pattern.find( m_engine_dll, "55 8B EC 83 EC 40 53 8B D9 8B 0D ? ? ? ? 89 5D F8" );
	m_draw_crosshair = m_pattern.find( m_client_dll, "55 8B EC 83 E4 F0 83 EC 78 56 8B F1 8B 0D ? ? ? ?" );
	m_update = m_pattern.find( m_client_dll, "E8 ? ? ? ? E9 ? ? ? ? 83 BE ? ? ? ? ?" ).relative( );
	m_modify_eye_position = m_pattern.find( m_client_dll, "E8 ? ? ? ? 8B 06 8B CE FF 90 ? ? ? ? 85 C0 74 50" ).relative( );
	m_do_procedural_foot_plant = m_pattern.find( m_client_dll, "E8 ? ? ? ? F6 86 ? ? ? ? ? 0F 84 ? ? ? ?" ).relative( );
	m_setup_velocity = m_pattern.find( m_client_dll, "55 8B EC 83 E4 F8 83 EC 30 56 57 8B 3D ? ? ? ?" );
	m_setup_movement = m_pattern.find( m_client_dll, "E8 ? ? ? ? 8B CF E8 ? ? ? ? 8B CF E8 ? ? ? ? 8B 47 60" ).relative( );
	m_setup_aim_matrix = m_pattern.find( m_client_dll, "55 8B EC 81 EC ? ? ? ? 53 56 57 8B 3D ? ? ? ?" );
	m_set_up_weapon_action = m_pattern.find( m_client_dll, "55 8B EC 51 53 56 57 8B F9 8B 77 60" );
	m_set_up_movement = m_pattern.find( m_client_dll, "E8 ? ? ? ? 8B CF E8 ? ? ? ? 8B CF E8 ? ? ? ? 8B 47 60" ).relative( );
	m_set_up_alive_loop = m_pattern.find( m_client_dll, "E8 ? ? ? ? 8B CF E8 ? ? ? ? 8B 47 60" ).relative( );
	m_set_up_whole_body_action = m_pattern.find( m_client_dll, "E8 ? ? ? ? 8B 47 60 83 B8 ? ? ? ? ?" ).relative( );
	m_set_up_flinch = m_pattern.find( m_client_dll, "E8 ? ? ? ? 8B CF E8 ? ? ? ? 33 C0" ).relative( );
	m_set_up_lean = m_pattern.find( m_client_dll, "E8 ? ? ? ? 33 C0 89 44 24 0C" ).relative( );
	m_cache_sequences = m_pattern.find( m_client_dll, "E8 ? ? ? ? 84 C0 0F 84 ? ? ? ? 8B 77 60" ).relative( );
	m_get_ground_entity = m_pattern.find( m_client_dll, "E8 ? ? ? ? 8B 4C 24 14 85 C0" ).relative( );
	m_invalidate_physics_recursive = m_pattern.find( m_client_dll, "E8 ? ? ? ? 89 5E 18" ).relative( );
	m_set_abs_angles = m_pattern.find( m_client_dll, "E8 ? ? ? ? 53 8D 45 F0" ).relative( );
	m_lookup_bone = m_pattern.find( m_client_dll, "E8 ? ? ? ? 89 44 24 5C" ).relative( );
	m_get_bone_position = m_pattern.find( m_client_dll, "E8 ? ? ? ? 8D 14 24" ).relative( );
	m_calc_absolute_velocity = m_pattern.find( m_client_dll, "E8 ? ? ? ? 83 7B 30 00" ).relative( );
	m_increment_layer_cycle = m_pattern.find( m_client_dll, "E8 ? ? ? ? FF 76 60 F3 0F 10 54 24 ?" ).relative( );
	m_increment_layer_weight = m_pattern.find( m_client_dll, "E8 ? ? ? ? 8B 5F 60 83 BB ? ? ? ? ?" ).relative( );
	m_get_model_ptr = m_pattern.find( m_client_dll, "E8 ? ? ? ? 8B 55 38" ).relative( );
	m_get_first_sequence_anim_tag = m_pattern.find( m_client_dll, "E8 ? ? ? ? F3 0F 11 86 ? ? ? ? 0F 57 DB" ).relative( );
	m_seqdesc = m_pattern.find( m_client_dll, "E8 ? ? ? ? 03 40 04" ).relative( );
	m_lookup_pose_parameter = m_pattern.find( m_client_dll, "E8 ? ? ? ? 85 C0 79 08" ).relative( );
	m_studio_set_pose_parameter = m_pattern.find( m_client_dll, "E8 ? ? ? ? 0F 28 D8 83 C4 04" ).relative( );
	m_cam_think = m_pattern.find( m_client_dll, "55 8B EC 83 E4 F8 81 EC ? ? ? ? 56 8B F1 8B 0D ? ? ? ? 57 85 C9" );
	m_cam_to_third_person = m_pattern.find( m_client_dll, "55 8B EC 83 EC 0C 8D 55 F4" );
	m_get_sequence_activity = m_pattern.find( m_client_dll, "E8 ? ? ? ? 33 C9 3B F0" ).relative( );

	m_start_drawing = m_pattern.find( m_vguimatsurface_dll, "55 8B EC 83 E4 C0 83 EC 38" );
	m_finish_drawing = m_pattern.find( m_vguimatsurface_dll, "8B 0D ? ? ? ? 56 C6 05 ? ? ? ? ?" );
	m_lock_cursor = m_pattern.find( m_vguimatsurface_dll, "80 3D ? ? ? ? ? 8B 91 ? ? ? ? 8B 0D ? ? ? ? C6 05 ? ? ? ? ? 8B 01 74 0B FF 35 ? ? ? ? 52 FF 50 34 C3 6A 00 52 FF 50 34 C3 55" );

	m_reload_schemes = m_pattern.find( m_vgui2_dll, "55 8B EC 83 EC 08 53 56 8B F1 6A 00" );

	m_draw_model = m_pattern.find( m_studiorender_dll, "55 8B EC 83 E4 F8 83 EC 54" );

	m_hook = m_pattern.find( m_gameoverlayrenderer_dll, "55 8B EC 51 8B 45 10 C7" );
	m_restore = m_pattern.find( m_gameoverlayrenderer_dll, "E8 ? ? ? ? 83 C4 08 FF 15 ? ? ? ?" ).relative( );

	m_draw_server_hitboxes = m_pattern.find( m_server_dll, "E8 ? ? ? ? F6 83 ? ? ? ? ? 0F 84 ? ? ? ? 33 FF" ).relative( );
	m_util_player_by_index = m_pattern.find( m_server_dll, "85 C9 7E 2A A1 ? ? ? ?" );
	m_server_setup_velocity = m_pattern.find( m_server_dll, "55 8B EC 83 E4 F8 83 EC 28 56 57 8B 3D ? ? ? ? 8B F1 8B CF" );

	return true;

}