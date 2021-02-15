#pragma once

#include "../signatures.h"

using h_font = unsigned long;

enum font_draw_type {

	font_draw_default = 0,
	font_draw_nonadditive,
	font_draw_additive,
	font_draw_type_count = 2,

};

enum font_flags {

	fontflag_none,
	fontflag_italic = 0x001,
	fontflag_underline = 0x002,
	fontflag_strikeout = 0x004,
	fontflag_symbol = 0x008,
	fontflag_antialias = 0x010,
	fontflag_gaussianblur = 0x020,
	fontflag_rotary = 0x040,
	fontflag_dropshadow = 0x080,
	fontflag_additive = 0x100,
	fontflag_outline = 0x200,
	fontflag_custom = 0x400,
	fontflag_bitmap = 0x800,

};

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

	inline auto draw_set_text_font( h_font font ) {

		return m_utils.get_v_func< void( __thiscall* )( void*, h_font ) >( this, 23 )( this, font );

	}

	inline auto draw_set_text_color( int r, int g, int b, int a ) {

		return m_utils.get_v_func< void( __thiscall* )( void*, int, int, int, int ) >( this, 25 )( this, r, g, b, a );

	}

	inline auto draw_set_text_pos( int x, int y ) {

		return m_utils.get_v_func< void( __thiscall* )( void*, int, int ) >( this, 26 )( this, x, y );

	}

	inline auto draw_print_text( const wchar_t* text, int text_len, font_draw_type draw_type = font_draw_default ) {

		return m_utils.get_v_func< void( __thiscall* )( void*, const wchar_t*, int, font_draw_type ) >( this, 28 )( this, text, text_len, draw_type );

	}

	inline auto get_screen_size( int& wide, int& tall ) {

		return m_utils.get_v_func< void( __thiscall* )( void*, int&, int& ) >( this, 44 )( this, wide, tall );

	}

	inline auto create_font( ) {

		return m_utils.get_v_func< h_font( __thiscall* )( void* ) >( this, 71 )( this );

	}

	inline auto set_font_glyph( h_font font, const char* windows_font_name, int tall, int weight, int blur, int scanlines, int flags, int range_min = 0, int range_max = 0 ) {

		return m_utils.get_v_func< void( __thiscall* )( void*, h_font, const char*, int, int, int, int, int, int, int ) >( this, 72 )( this, font, windows_font_name, tall, weight, blur, scanlines, flags, range_min, range_max  );

	}

	inline auto get_text_size( h_font font, const wchar_t* text, int& wide, int& tall ) {

		return m_utils.get_v_func< void( __thiscall* )( void*, h_font, const wchar_t*, int&, int& ) >( this, 79 )( this, font, text, wide, tall );

	}

	inline auto start_drawing( ) {

		auto function = m_signatures.m_start_drawing.as< void( __thiscall* )( void* ) >( );

		return function( this );

	}

	inline auto finish_drawing( ) {

		auto function = m_signatures.m_finish_drawing.as< void( __thiscall* )( void* ) >( );

		return function( this );

	}

};