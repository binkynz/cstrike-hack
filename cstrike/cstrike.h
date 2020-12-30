#pragma once

#include "../other/other.h"
#include "../valve/valve.h"

struct cstrike {

	static DWORD WINAPI setup( void* parameter );

	void unload( );

	base_player* m_local_player;

};

inline cstrike m_cstrike;