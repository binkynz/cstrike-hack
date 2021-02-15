#pragma once

#include "../cstrike.h"

enum render_flags {

	x_right = 1,
	x_centre = 1 << 1,
	
	y_bottom = 1 << 2,
	y_centre = 1 << 3,

};

struct render {

	bool setup( );

	void draw_line( int x0, int y0, int x1, int y1, const color& color );

	void draw_filled_rect( int x, int y, int width, int height, const color& color, int flags = { } );

	void draw_outlined_rect( int x, int y, int width, int height, const color& color, int flags = { } );

	void draw_text( h_font& font, int x, int y, std::wstring_view text, const color& color, int flags = { } );

	void draw_text( h_font& font, int x, int y, std::string_view text, const color& color, int flags = { } );

	struct {

		h_font main;

	} m_fonts;

private:

	bool create_font( h_font& font, std::string_view name, int tall, int weight, int flags = { } );

	void handle_flags( int& x, int& y, int width, int height, int flags );

};

inline render m_render;