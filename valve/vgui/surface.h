#pragma once

#include "../../other/pattern/pattern.h"

struct surface {

	inline auto draw_set_color( int r, int g, int b, int a ) {

		return m_utils.get_v_func< void( __thiscall* )( void*, int, int, int, int ) >( this, 15 )( this, r, g, b, a );

	}

	inline auto draw_filled_rect( int x0, int y0, int x1, int y1 ) {

		return m_utils.get_v_func< void( __thiscall* )( void*, int, int, int, int ) >( this, 16 )( this, x0, y0, x1, y1 );

	}

	inline auto draw_outlined_rect( int x0, int y0, int x1, int y1 ) {

		return m_utils.get_v_func< void( __thiscall* )( void*, int, int, int, int ) >( this, 18 )( this, x0, y0, x1, y1 );

	}

	inline auto draw_line( int x0, int y0, int x1, int y1 ) {

		return m_utils.get_v_func< void( __thiscall* )( void*, int, int, int, int ) >( this, 19 )( this, x0, y0, x1, y1 );

	}

	inline auto get_screen_size( int& wide, int& tall ) {

		return m_utils.get_v_func< void( __thiscall* )( void*, int&, int& ) >( this, 44 )( this, wide, tall );

	}

	inline auto start_drawing( ) {

		static auto function = m_pattern.find( "vguimatsurface.dll", "55 8B EC 83 E4 C0 83 EC 38" ).as< void( __thiscall* )( void* ) >( );

		return function( this );

	}

	inline auto finish_drawing( ) {

		static auto function = m_pattern.find( "vguimatsurface.dll", "8B 0D ? ? ? ? 56 C6 05 ? ? ? ? ?" ).as< void( __thiscall* )( void* ) >( );

		return function( this );

	}

};