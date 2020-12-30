#pragma once

#include "../other/utils/utils.h"

struct client_class;

struct base_client_dll {

	inline auto get_all_classes( ) {

		return m_utils.get_v_func< client_class* ( __thiscall* )( void* ) >( this, 8 )( this );

	}

};