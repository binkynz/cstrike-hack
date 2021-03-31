#pragma once

#include "../cstrike.h"

#include "../features/features.h"
#include "../input/input.h"

struct hooked {

	bool setup( );

	void unload( );

private:

	static void __fastcall level_shutdown( void* ecx, void* edx );
	static bool __fastcall create_move( void* ecx, void* edx, float input_sample_time, user_cmd* cmd );
	static float __fastcall get_view_model_fov( void* ecx, void* edx );
	static void __fastcall paint( engine_vgui* ecx, void* edx, paint_mode mode );
	static void __fastcall draw_crosshair( weapon_cs_base* ecx, void* edx );
	static void __vectorcall update( csgo_player_anim_state* ecx, void* unk0, float z, float y, float x, void* unk1 );
	static void __fastcall modify_eye_position( csgo_player_anim_state* ecx, void* edx, vector_3d& input_eye_pos );
	static void __fastcall do_procedural_foot_plant( csgo_player_anim_state* ecx, void* edx, void* bone_to_world, void* left_foot_chain, void* right_foot_chain, void* pos );
	static void __fastcall set_up_movement( csgo_player_anim_state* ecx, void* edx );
	static void __fastcall set_up_velocity( csgo_player_anim_state* ecx, void* edx );
	static void __fastcall cam_think( client_input* ecx, void* edx );
	static void __fastcall cam_to_third_person( client_input* ecx, void* edx );
	static void __fastcall reload_schemes( void* ecx, void* edx );
	static void __fastcall draw_model( studio_render_context* ecx, void* edx, void* results, const draw_model_info& info, void* bone_to_world, float* flex_weights, float* flex_delayed_rates, const vector_3d& origin, int flags );
	static void __fastcall lock_cursor( surface* ecx, void* edx );

};

inline hooked m_hooked;