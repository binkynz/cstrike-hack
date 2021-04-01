#include "key.h"

#include "../../menu.h"

key::key( std::string_view name, int x, int y ) : object( name, x, y ) {

	set_size( 0, 0 );
	set_item( nullptr );

}

void key::set_size( int width, int height ) {

	m_width = width;
	m_height = height;

}

void key::set_item( int* item ) {

	m_item = item;

}

void key::draw( ) {

	int x = m_menu.m_size.x + m_size.x,
		y = m_menu.m_size.y + m_size.y;

	m_render.draw_outlined_rect( x, y,
		m_width, m_height,
		m_menu.m_colors.light );

	m_render.draw_text( m_render.m_fonts.main,
		x + m_width / 2, y,
		m_render.format_text( "%d", *m_item ),
		m_menu.m_colors.light,
		x_centre );

	m_render.draw_text( m_render.m_fonts.main,
		x + m_width + m_gap, y,
		m_name,
		m_menu.m_colors.light );

}

void key::think( ) {

	int x = m_menu.m_size.x + m_size.x,
		y = m_menu.m_size.y + m_size.y;

	if ( m_input.is_key_toggled( VK_LBUTTON )
		&& m_input.is_mouse_in_bounds( x, y, m_width, m_height ) ) {

		m_active = true;
		m_input.set_last_key( );

	}
	
	if ( !m_active )
		return;

	int key = m_input.get_last_key( );
	if ( key == -1 )
		return;

	if ( key != VK_ESCAPE )
		*m_item = key;

	m_active = false;

}