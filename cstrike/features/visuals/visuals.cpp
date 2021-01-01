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

		}, { iterate_dormant } );

}

void visuals::draw_box( ) {

	color box_color = color( 255, 255, 255, m_alpha.at( m_player.index - 1 ) );

	m_render.draw_outlined_rect( m_box.x - 1, m_box.y - 1, m_box.width + 2, m_box.height + 2, color( 0, 0, 0, 220 ) );
	m_render.draw_outlined_rect( m_box.x + 1, m_box.y + 1, m_box.width - 2, m_box.height - 2, color( 0, 0, 0, 220 ) );
	m_render.draw_outlined_rect( m_box.x, m_box.y, m_box.width, m_box.height, box_color );

}

void visuals::draw_health( ) {

	int health = m_player.pointer->get_health( );

	int scaler = static_cast< int >( 2.55 * health );
	color health_color = color( 255 - scaler, scaler, 0, m_alpha.at( m_player.index - 1 ) );

	m_render.draw_filled_rect( m_box.x - 2, m_box.y - 1, 4, m_box.height + 2, color( 0, 0, 0, 220 ), origin_right );
	m_render.draw_filled_rect( m_box.x - 3, m_box.y, 2, health * m_box.height / 100, health_color, origin_right );

}

void visuals::calculate_alpha( ) {

	float delta_time = m_interfaces.m_globals->m_curtime - m_player.pointer->get_simulation_time( );

	float opacity = m_player.is_dormant ? std::clamp( 1.f - delta_time / 0.5f, 0.f, 1.f ) : 1.f;

	m_alpha.at( m_player.index - 1 ) = static_cast< int >( 255 * opacity );

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