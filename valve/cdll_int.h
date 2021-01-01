#pragma once

#include "../other/utils/utils.h"

struct client_class;

using player_info = struct {

	char _pad0[ 0x8 ];
	int m_xuid_low;
	char _pad1[ 0x4 ];
	char m_name[ 256 ];
	char _pad2[ 0x13c ];

};

struct engine_client {

	inline auto get_player_info( int ent_num, player_info* info ) {

		return m_utils.get_v_func< bool( __thiscall* )( void*, int, player_info* ) >( this, 8 )( this, ent_num, info );

	}

};

struct base_client_dll {

	inline auto get_all_classes( ) {

		return m_utils.get_v_func< client_class* ( __thiscall* )( void* ) >( this, 8 )( this );

	}

};