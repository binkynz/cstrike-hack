#include "visuals.h"

#include "../../render/render.h"

void visuals::paint( ) {

	m_cstrike.iterate_players( [ ]( cs_player* player ) -> void {

		vector_3d origin = player->get_origin( ), screen_origin;
		if ( m_interfaces.m_debug_overlay->screen_position( origin, screen_origin ) == -1 )
			return;

		int x = static_cast< int >( screen_origin.x ), y = static_cast< int >( screen_origin.y );
		m_render.draw_filled_rect( x - 5, y - 5, 10, 10, color( 255, 255, 255 ) );

		}, { } );

}