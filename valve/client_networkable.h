#pragma once

struct client_networkable {

	inline auto is_dormant( ) {

		return m_utils.get_v_func< bool( __thiscall* )( void* ) >( this, 9 )( this );

	}

};