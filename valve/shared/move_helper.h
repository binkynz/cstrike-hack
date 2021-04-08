#pragma once

struct move_helper {

	inline auto process_impacts( ) {

		return m_utils.get_v_func< void( __thiscall* )( void* ) >( this, 4 )( this );

	}

};