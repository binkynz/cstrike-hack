#pragma once

#include <functional>

#include "config.h"

#include "../other/other.h"
#include "../valve/valve.h"

enum iterate_player_flags {

	iterate_dead = 1,
	iterate_dormant = 1 << 1,
	iterate_teammates = 1 << 2,

};

struct cstrike {

	static DWORD WINAPI setup( void* parameter );

	void unload( );

	void iterate_players( std::function< void( cs_player* ) > function, int flags = { } );

	HWND m_window;

	base_player* m_local_player;

};

inline cstrike m_cstrike;