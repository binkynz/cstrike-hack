#include "menu.h"

#include "../input/input.h"
#include "../render/render.h"

bool menu::setup( ) {

	m_size.x = 100;
	m_size.y = 100;
	m_size.width = 700;
	m_size.height = 400;
	m_size.gap = 25;

	m_colors.dark = color( 20, 20, 20 );
	m_colors.light = color( 255, 255, 255 );
	m_colors.vibrant = color( 255, 255, 0 );

	m_selected_tab = 0;

	setup_tab( "legit", [ ]( tab* tab ) -> void {

		tab->setup_group( 25, 50, 320, 325, [ ]( group* group ) -> void {

			} );

		tab->setup_group( 355, 50, 320, 325, [ ]( group* group ) -> void {

			} );

		} );

	setup_tab( "hvh", [ ]( tab* tab ) -> void {

		tab->setup_group( 25, 50, 320, 325, [ ]( group* group ) -> void {

			} );

		tab->setup_group( 355, 50, 320, 325, [ ]( group* group ) -> void {

			} );

		} );

	setup_tab( "esp", [ ]( tab* tab ) -> void {

		tab->setup_group( 25, 50, 320, 325, [ ]( group* group ) -> void {

			group->setup_checkbox( "enable", &m_config.m_esp.active );
			group->setup_checkbox( "player box", &m_config.m_esp.player_box );
			group->setup_checkbox( "player health", &m_config.m_esp.player_health );
			group->setup_checkbox( "player name", &m_config.m_esp.player_name );
			group->setup_checkbox( "player weapon", &m_config.m_esp.player_weapon );

			} );

		tab->setup_group( 355, 50, 320, 325, [ ]( group* group ) -> void {

			group->setup_checkbox( "chams", &m_config.m_esp.chams );
			group->setup_key( "thirdperson key", &m_config.m_esp.thirdperson_key );
			group->setup_slider( "thirdperson distance", &m_config.m_esp.thirdperson_distance, 30, 170 );

			} );

		} );

	setup_tab( "misc", [ ]( tab* tab ) -> void {

		tab->setup_group( 25, 50, 320, 325, [ ]( group* group ) -> void {

			group->setup_slider( "viewmodel fov", &m_config.m_misc.viewmodel_fov, 60, 120 );

			} );

		tab->setup_group( 355, 50, 320, 325, [ ]( group* group ) -> void {

			group->setup_checkbox( "server hitboxes", &m_config.m_misc.server_hitboxes );

			} );

		} );

	return true;

}

void menu::paint( ) {

	if ( !m_input.is_key_toggled( VK_INSERT, m_config.m_menu_open ) )
		return;

	handle_movement( );

	draw_backplate( );

	process_tabs( );

}

void menu::setup_tab( std::string_view name, std::function< void( tab* ) > function ) {

	tab tab( name );

	function( &tab );

	m_tabs.push_back( tab );

}

void menu::handle_movement( ) {

	if ( m_drag.active ) {

		m_size.x += m_input.get_mouse_x( ) - m_drag.x;
		m_size.y += m_input.get_mouse_y( ) - m_drag.y;

	} 

	if ( ( !m_drag.active ? m_input.is_key_toggled( VK_LBUTTON ) : m_input.is_mouse_down( VK_LBUTTON ) )
		&& ( m_input.is_mouse_in_bounds( m_size.x - 3, m_size.y - 3, m_size.width + 6, 3 )
		|| m_input.is_mouse_in_bounds( m_size.x - 3, m_size.y - 3, 3, m_size.height + 6 )
		|| m_input.is_mouse_in_bounds( m_size.x + m_size.width, m_size.y - 3, 3, m_size.height + 6 ) 
		|| m_input.is_mouse_in_bounds( m_size.x - 3, m_size.y + m_size.height, m_size.width + 6, 3 ) ) ) {

		m_drag.active = true;
		m_drag.x = m_input.get_mouse_x( );
		m_drag.y = m_input.get_mouse_y( );

	} else {

		m_drag.active = false;

	}

}

void menu::draw_backplate( ) {

	color low_alpha_main = m_colors.dark;
	low_alpha_main.a = 60;

	m_render.draw_outlined_rect( m_size.x - 3, m_size.y - 3,
		m_size.width + 6, m_size.height + 6,
		low_alpha_main );

	m_render.draw_outlined_rect( m_size.x - 2, m_size.y - 2,
		m_size.width + 4, m_size.height + 4,
		m_colors.dark );

	m_render.draw_outlined_rect( m_size.x - 1, m_size.y - 1,
		m_size.width + 2, m_size.height + 2,
		low_alpha_main );

	m_render.draw_filled_rect( m_size.x, m_size.y,
		m_size.width, m_size.height,
		m_colors.dark );

}

void menu::process_tabs( ) {

	int	start_x = m_size.x + m_size.gap,
		start_y = m_size.y + m_size.gap,
		end_x = m_size.x + m_size.width - m_size.gap;

	int total_width = end_x - start_x;
	for ( std::size_t i = 0; i < m_tabs.size( ); i++ ) {

		int width = ( total_width / ( m_tabs.size( ) + 1 ) ),
			x = start_x + width * ( i + 1 );

		m_render.draw_line( x - width / 2, start_y - 5,
			x - width / 2, start_y + 5,
			m_colors.light );
		m_render.draw_line( x + width / 2, start_y - 5,
			x + width / 2, start_y + 5,
			m_colors.light );

		if ( m_input.is_key_toggled( VK_LBUTTON )
			&& m_input.is_mouse_in_bounds( x - width / 2, start_y - 5, width, 10 ) )
			m_selected_tab = i;

		m_tabs[ i ].draw( x, start_y, i == m_selected_tab );

	}
		
}