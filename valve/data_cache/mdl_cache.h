#pragma once

struct mdl_cache {

	inline auto begin_lock( ) {

		return m_utils.get_v_func< void( __thiscall* )( void* ) >( this, 33 )( this );

	}

	inline auto end_lock( ) {

		return m_utils.get_v_func< void( __thiscall* )( void* ) >( this, 34 )( this );

	}

};