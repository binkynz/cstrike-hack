#pragma once

#include "../../other/math/vector_3d.h"

struct debug_overlay {

	inline auto screen_position( const vector_3d& point, vector_3d& screen ) {

		return m_utils.get_v_func< int( __thiscall* )( void*, const vector_3d&, vector_3d& ) >( this, 13 )( this, point, screen );

	}

};