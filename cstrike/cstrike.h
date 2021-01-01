#pragma once

#include <functional>

#include "features/features.h"

#include "../other/other.h"
#include "../valve/valve.h"

struct cstrike {

	static DWORD WINAPI setup( void* parameter );

	void unload( );

	enum iterate_player_flags {

		iterate_dead = 1,
		iterate_dormant = 1 << 1,
		iterate_teammates = 1 << 2,

	};

	void iterate_players( std::function< void( cs_player* ) > function, iterate_player_flags flags );

	base_player* m_local_player;

};

inline cstrike m_cstrike;