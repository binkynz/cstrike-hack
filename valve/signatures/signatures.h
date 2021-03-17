#pragma once

#include "../../other/pattern/pattern.h"

struct signatures {

	// needs nullptr checks to not be cringe
	bool setup( );

	// module names

	address m_client_dll;
	address m_engine_dll;
	address m_server_dll;
	address m_gameoverlayrenderer_dll;
	address m_vgui2_dll;
	address m_vguimatsurface_dll;
	address m_studiorender_dll;
	address m_localize_dll;
	address m_datacache_dll;
	address m_materialsystem_dll;

	// offsets

	address m_anim_overlay;
	address m_abs_velocity;

	// functions

	address m_level_shutdown;
	address m_create_move;
	address m_get_view_model_fov;
	address m_paint;
	address m_draw_crosshair;
	address m_update;
	address m_modify_eye_position;
	address m_do_procedural_foot_plant;
	address m_setup_velocity;
	address m_setup_movement;
	address m_setup_aim_matrix;
	address m_set_up_weapon_action;
	address m_set_up_movement;
	address m_set_up_alive_loop;
	address m_set_up_whole_body_action;
	address m_set_up_flinch;
	address m_set_up_lean;
	address m_cache_sequences;
	address m_get_ground_entity;
	address m_invalidate_physics_recursive;
	address m_set_abs_angles;
	address m_lookup_bone;
	address m_get_bone_position;
	address m_calc_absolute_velocity;
	address m_increment_layer_cycle;
	address m_increment_layer_weight;
	address m_get_model_ptr;
	address m_get_first_sequence_anim_tag;
	address m_seqdesc;
	address m_lookup_pose_parameter;
	address m_studio_set_pose_parameter;
	address m_cam_think;
	address m_cam_to_third_person;

	address m_start_drawing;
	address m_finish_drawing;

	address m_reload_schemes;

	address m_draw_model;

	address m_hook;
	address m_restore;

	address m_draw_server_hitboxes;
	address m_util_player_by_index;

};

inline signatures m_signatures;