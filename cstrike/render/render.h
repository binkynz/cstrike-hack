#pragma once

#include "../cstrike.h"

enum render_flags {

	origin_right = 1,
	origin_centre = 1 << 1,

};

struct render {

	void draw_line( int x0, int y0, int x1, int y1, const color& color );

	void draw_filled_rect( int x, int y, int width, int height, const color& color, render_flags flags = { } );

	void draw_outlined_rect( int x, int y, int width, int height, const color& color, render_flags flags = { } );

};

inline render m_render;