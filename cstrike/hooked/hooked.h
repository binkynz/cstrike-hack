#pragma once

#include "../cstrike.h"

#include "../features/features.h"

struct hooked {

	bool setup( );

	void unload( );

private:

	static bool __fastcall create_move( base_player* ecx, void* edx, float input_sample_time, user_cmd* cmd );
	static void __fastcall paint( void* ecx, void* edx, paint_mode mode );
	static float __fastcall get_view_model_fov( void* ecx, void* edx );
	static bool __fastcall should_interpolate( base_entity* ecx, void* edx );
	static void __fastcall draw_crosshair( weapon_cs_base* ecx, void* edx );

};

inline hooked m_hooked;