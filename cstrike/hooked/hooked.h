#pragma once

#include "../cstrike.h"

#include "../features/features.h"

namespace hooked {

	bool setup( );

	void unload( );

	inline detour m_create_move;
	inline detour m_paint;

	namespace functions {

		bool __fastcall create_move( base_player* ecx, void* edx, float input_sample_time, user_cmd* cmd );
		void __fastcall paint( void* ecx, void* edx, paint_mode mode );

	}

}