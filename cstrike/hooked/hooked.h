#pragma once

#include "../cstrike.h"

#include "../features/features.h"

struct hooked {

	bool setup( );

	void unload( );

private:

	static bool __fastcall create_move( base_player* ecx, void* edx, float input_sample_time, user_cmd* cmd );
	static void __fastcall paint( void* ecx, void* edx, paint_mode mode );

};

inline hooked m_hooked;