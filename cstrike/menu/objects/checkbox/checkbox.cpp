#include "checkbox.h"

#include "../../menu.h"

checkbox::checkbox( std::string_view name, int x, int y ) : object( name, x, y ) {

	set_size( 0 );
	set_item( nullptr );

}

void checkbox::set_size( int size ) {

	m_height = size;

}

void checkbox::set_item( bool* item ) {

	m_item = item;

}

void checkbox::draw( ) {

	int x = m_menu.m_size.x + m_size.x,
		y = m_menu.m_size.y + m_size.y;

	m_render.draw_filled_rect( x, y, 
		m_height, m_height, 
		*m_item ? color( 255, 255, 255 ) : color( 255, 255, 255, 100 ) );

	m_render.draw_text( m_render.m_fonts.main,
		x + m_height + m_gap, y,
		m_name,
		color( 255, 255, 255 ) );

}

void checkbox::think( ) {

	int x = m_menu.m_size.x + m_size.x,
		y = m_menu.m_size.y + m_size.y;

	if ( !m_input.is_key_toggled( VK_LBUTTON )
		|| !m_input.is_mouse_in_bounds( x, y, m_height, m_height ) )
		return;

	*m_item = !*m_item;

}