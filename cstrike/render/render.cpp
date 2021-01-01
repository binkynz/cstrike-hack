#include "render.h"

void render::draw_line( int x0, int y0, int x1, int y1, const color& color ) {

	m_interfaces.m_surface->draw_set_color( color.r, color.g, color.b, color.a );

	m_interfaces.m_surface->draw_line( x0, y0, x1, y1 );

}

void render::draw_filled_rect( int x, int y, int width, int height, const color& color ) {

	m_interfaces.m_surface->draw_set_color( color.r, color.g, color.b, color.a );

	m_interfaces.m_surface->draw_filled_rect( x, y, x + width, y + height );

}

void render::draw_outlined_rect( int x, int y, int width, int height, const color& color ) {

	m_interfaces.m_surface->draw_set_color( color.r, color.g, color.b, color.a );

	m_interfaces.m_surface->draw_outlined_rect( x, y, x + width, y + height );

}