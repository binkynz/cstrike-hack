#pragma once

#include "../cstrike.h"

namespace hooked {

	bool setup( );

	void unload( );

	inline detour m_create_move;

	namespace functions {

		bool __fastcall create_move( base_player* ecx, void* edx, float input_sample_time, user_cmd* cmd );

	}

}