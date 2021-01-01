#pragma once

#include "../cstrike.h"

struct render {

	void draw_line( int x0, int y0, int x1, int y1, const color& color );

	void draw_filled_rect( int x, int y, int width, int height, const color& color );

	void draw_outlined_rect( int x, int y, int width, int height, const color& color );

};

inline render m_render;