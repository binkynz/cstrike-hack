#pragma once

struct localize {

	inline auto find( char const* token_name ) {

		return m_utils.get_v_func< wchar_t* ( __thiscall* )( void*, char const* ) >( this, 11 )( this, token_name );

	}

};