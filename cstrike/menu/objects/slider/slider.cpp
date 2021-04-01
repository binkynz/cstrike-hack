#include "slider.h"

#include "../../menu.h"

slider::slider( std::string_view name, int x, int y ) : object( name, x, y ) { 

	set_size( 0, 0 );
	set_item( nullptr );
	set_range( 0, 0 );

}

void slider::set_size( int width, int height ) {

	m_width = width;
	m_height = height;

}

void slider::set_item( int* item ) {

	m_item = item;

}

void slider::set_range( int min, int max ) {

	m_min = min;
	m_max = max;

}

void slider::draw( ) {

	int x = m_menu.m_size.x + m_size.x,
		y = m_menu.m_size.y + m_size.y;

	m_render.draw_outlined_rect( x, y,
		m_width, m_height,
		m_menu.m_colors.light );

	int width = ( *m_item - m_min ) * m_width / ( m_max - m_min );

	m_render.draw_filled_rect( x + 1, y + 1,
		width - 2, m_height - 2,
		*m_item ? m_menu.m_colors.vibrant : m_menu.m_colors.light );

	m_render.draw_text( m_render.m_fonts.main,
		x + m_width + m_gap, y,
		m_render.format_text( "%s - %d", m_name.data( ), *m_item ),
		color( 255, 255, 255 ) );

}

void slider::think( ) {

	int x = m_menu.m_size.x + m_size.x,
		y = m_menu.m_size.y + m_size.y;

	if ( ( !m_active ? m_input.is_key_toggled( VK_LBUTTON ) : m_input.is_mouse_down( VK_LBUTTON ) )
		&& m_input.is_mouse_in_bounds( x, y, m_width, m_height ) )
		m_active = true;

	if ( !m_active )
		return;

	if ( !m_input.is_mouse_down( VK_LBUTTON ) )
		m_active = false;

	*m_item = std::clamp( m_min + ( m_max - m_min ) * ( m_input.get_mouse_x( ) - x ) / m_width, m_min, m_max );

}