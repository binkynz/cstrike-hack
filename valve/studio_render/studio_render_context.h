#pragma once

struct studio_render_context {

	inline auto set_colour_modulation( float const* color ) {

		return m_utils.get_v_func< void( __thiscall* )( void*, float const* ) >( this, 27 )( this, color );

	}

	inline auto set_alpha_modulation( float alpha ) {

		return m_utils.get_v_func< void( __thiscall* )( void*, float ) >( this, 28 )( this, alpha );

	}

};