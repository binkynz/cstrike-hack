#pragma once

struct material {

	inline auto set_material_var_flag( int flag, bool on ) {

		return m_utils.get_v_func< void( __thiscall* )( void*, int, bool ) >( this, 29 )( this, flag, on );

	}

};