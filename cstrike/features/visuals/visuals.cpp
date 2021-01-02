#include "visuals.h"

#include <algorithm>

#include "../../render/render.h"

void visuals::paint( ) {

	m_cstrike.iterate_players( [ this ]( cs_player* player ) -> void {

		m_player = {

			player,
			player->get_client_networkable( )->get_index( ),
			player->get_client_networkable( )->is_dormant( ),

		};

		if ( !calculate_box( ) )
			return;

		calculate_alpha( );

		draw_box( );

		draw_health( );

		draw_name( );

		draw_weapon( );

		}, { iterate_dormant } );

}

void visuals::draw_box( ) {

	m_render.draw_outlined_rect( m_box.x - 1, m_box.y - 1, 
		m_box.width + 2, m_box.height + 2, 
		color( 0, 0, 0, m_alpha[ m_player.index - 1 ] ) );

	m_render.draw_outlined_rect( m_box.x + 1, m_box.y + 1, 
		m_box.width - 2, m_box.height - 2, 
		color( 0, 0, 0, m_alpha[ m_player.index - 1 ] ) );

	m_render.draw_outlined_rect( m_box.x, m_box.y,
		m_box.width, m_box.height, 
		color( 255, 255, 255, m_alpha[ m_player.index - 1 ] ) );

}

void visuals::draw_health( ) {

	int health = m_player.pointer->get_health( ), 
		scaler = static_cast< int >( 2.55 * health );

	m_render.draw_filled_rect( m_box.x - 2, m_box.y - 1, 
		4, m_box.height + 2, 
		color( 0, 0, 0, m_alpha[ m_player.index - 1 ] ), 
		x_right );

	m_render.draw_filled_rect( m_box.x - 3, m_box.y, 
		2, health * m_box.height / 100, 
		color( 255 - scaler, scaler, 0, m_alpha[ m_player.index - 1 ] ),
		x_right );

	if ( health == 100 )
		return;

	m_render.draw_text( m_font, 
		m_box.x - 7, m_box.y + health * m_box.height / 100 + 1, 
		std::to_wstring( health ), 
		color( 255, 255, 255, m_alpha[ m_player.index - 1 ] ), 
		x_right | y_centre );

}

void visuals::draw_name( ) {

	player_info info;
	if ( !m_interfaces.m_engine->get_player_info( m_player.index, &info ) )
		return;

	std::string name = info.m_name;
	std::transform( name.begin( ), name.end( ), name.begin( ), std::tolower );

	if ( !info.m_xuid_low )
		name.append( " - bot" );

	m_render.draw_text( m_font, 
		m_box.x + m_box.width / 2, m_box.y - 1, 
		name, 
		color( 255, 255, 255, m_alpha[ m_player.index - 1 ] ), 
		x_centre | y_bottom );

}

void visuals::draw_weapon( ) {

	weapon_cs_base_gun* weapon = m_interfaces.m_entity_list->get< weapon_cs_base_gun* >( m_player.pointer->get_active_weapon( ) );
	if ( !weapon )
		return;

	cs_weapon_info* weapon_info = weapon->get_cs_wpn_data( );
	if ( !weapon_info )
		return;

	std::wstring weapon_name = m_interfaces.m_localize->find( weapon_info->m_hud_name );
	std::transform( weapon_name.begin( ), weapon_name.end( ), weapon_name.begin( ), std::tolower );

	m_render.draw_text( m_font,
		m_box.x + m_box.width / 2, m_box.y + m_box.height + 2,
		weapon_name,
		color( 255, 255, 255, m_alpha[ m_player.index - 1 ] ),
		x_centre );

}

void visuals::calculate_alpha( ) {

	float delta_time = m_interfaces.m_globals->m_curtime - m_player.pointer->get_simulation_time( );

	double opacity = m_player.is_dormant ? m_easing.in_cubic( 1.0 - std::clamp( delta_time, 0.f, 1.f ) ) : 1.0;

	m_alpha[ m_player.index - 1 ] = static_cast< int >( 255 * opacity );

}

bool visuals::calculate_box( ) {

	vector_3d mins, maxs;
	m_player.pointer->get_client_renderable( )->get_render_bounds( mins, maxs );

	vector_3d origin = m_player.pointer->get_origin( ), screen_origin;
	origin.z -= 5.f;

	vector_3d top = m_player.pointer->get_origin( ), screen_top;
	top.z += maxs.z;

	if ( m_interfaces.m_debug_overlay->screen_position( origin, screen_origin ) == -1
		|| m_interfaces.m_debug_overlay->screen_position( top, screen_top ) == -1 )
		return false;

	float height = screen_origin.y - screen_top.y;
	float width = height / 2;

	m_box = {

		static_cast< int >( screen_origin.x - width / 2 ),
		static_cast< int >( screen_top.y ),
		static_cast< int >( width ),
		static_cast< int >( height )

	};

	return true;

}