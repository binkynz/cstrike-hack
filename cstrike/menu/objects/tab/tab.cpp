#include "tab.h"

#include "../../menu.h"

tab::tab( std::string_view name ) {

	m_name = name;

}

void tab::draw( int x, int y, bool is_selected ) {

	m_render.draw_text( m_render.m_fonts.main, x, y, 
		m_name, 
		is_selected ? m_menu.m_colors.vibrant : m_menu.m_colors.light,
		x_centre | y_centre );

	if ( !is_selected )
		return;

	for ( auto g : m_groups )
		g.draw( );

}

void tab::setup_group( int x, int y, int width, int height, std::function< void( group* ) > function ) {

	group group( x, y, width, height );

	function( &group );

	m_groups.push_back( group );

}