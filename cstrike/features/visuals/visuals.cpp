#include "visuals.h"

#include <algorithm>

#include "../../render/render.h"

void visuals::paint( ) {

	draw_watermark( );

	draw_local_info( );

	if ( !m_config.m_esp.active )
		return;

	m_cstrike.iterate_players( [ this ]( cs_player* player ) -> void {

		m_player = {

			player,
			player->get_client_networkable( )->get_index( ),
			player->get_client_networkable( )->is_dormant( ),

		};

		if ( !calculate_box( ) )
			return;

		m_weapon.pointer = m_interfaces.m_entity_list->get< weapon_cs_base* >( m_player.pointer->get_active_weapon( ) );
		if ( m_weapon.pointer )
			m_weapon.info = m_weapon.pointer->get_cs_wpn_data( );

		calculate_alpha( );

		m_player.m_colors.dark = color( 0, 0, 0, m_alpha[ m_player.index - 1 ] );
		m_player.m_colors.light = color( 255, 255, 255, m_alpha[ m_player.index - 1 ] );

		draw_box( );

		draw_health( );

		draw_name( );

		draw_weapon( );

		draw_ammo( );

		}, { iterate_dormant } );

}

void visuals::draw_watermark( ) {

	int fps = static_cast< int >( 1.f / m_interfaces.m_net_graph_panel->m_frame_rate );

	m_render.draw_text( m_render.m_fonts.main,
		m_render.m_screen.w - 5, 5,
		m_render.format_text( "%s | local: 0x%x | fps: %d", "cstrike-hack", m_cstrike.m_local_player, fps ),
		color( 255, 255, 255 ),
		x_right );

}

void visuals::draw_local_info( ) {

	if ( !m_cstrike.m_local_player )
		return;

	csgo_player_anim_state* anim_state = m_cstrike.m_local_player->get_player_anim_state_csgo( );
	if ( !anim_state )
		return;

	float lower_body_realign_time_remaining = std::fmaxf( 0.f, anim_state->m_lower_body_realign_timer - m_interfaces.m_globals->m_curtime );

	m_render.draw_text( m_render.m_fonts.main,
		5, m_render.m_screen.h / 2,
		m_render.format_text( "lby update in: %g", lower_body_realign_time_remaining ),
		color( 255, 255, 255 ) );

}

void visuals::draw_box( ) {

	if ( !m_config.m_esp.player_box )
		return;

	m_render.draw_outlined_rect( m_box.x - 1, m_box.y - 1, 
		m_box.width + 2, m_box.height + 2, 
		m_player.m_colors.dark );

	m_render.draw_outlined_rect( m_box.x + 1, m_box.y + 1, 
		m_box.width - 2, m_box.height - 2, 
		m_player.m_colors.dark );

	m_render.draw_outlined_rect( m_box.x, m_box.y,
		m_box.width, m_box.height, 
		m_player.m_colors.light );

}

void visuals::draw_health( ) {

	if ( !m_config.m_esp.player_health )
		return;

	int health = m_player.pointer->get_health( ), 
		scaler = static_cast< int >( 2.55 * health );

	m_render.draw_filled_rect( m_box.x - 2, m_box.y - 1, 
		4, m_box.height + 2, 
		m_player.m_colors.dark,
		x_right );

	m_render.draw_filled_rect( m_box.x - 3, m_box.y, 
		2, health * m_box.height / 100, 
		color( 255 - scaler, scaler, 0, m_alpha[ m_player.index - 1 ] ),
		x_right );

	if ( health == 100 )
		return;

	m_render.draw_text( m_render.m_fonts.main, 
		m_box.x - 7, m_box.y + health * m_box.height / 100, 
		m_render.format_text( "%d", health ),
		m_player.m_colors.light,
		x_right | y_centre );

}

void visuals::draw_name( ) {

	if ( !m_config.m_esp.player_name )
		return;

	player_info info;
	if ( !m_interfaces.m_engine->get_player_info( m_player.index, &info ) )
		return;

	std::string name = info.m_name;
	std::transform( name.begin( ), name.end( ), name.begin( ), std::tolower );

	if ( !info.m_xuid_low )
		name.append( " - bot" );

	m_render.draw_text( m_render.m_fonts.main,
		m_box.x + m_box.width / 2, m_box.y - 1, 
		name, 
		m_player.m_colors.light,
		x_centre | y_bottom );

}

void visuals::draw_weapon( ) {

	if ( !m_config.m_esp.player_weapon )
		return;

	if ( !m_weapon.pointer )
		return;

	int gap = m_config.m_esp.player_ammo ? 5 : 0;

	std::wstring weapon_name = m_interfaces.m_localize->find( m_weapon.info->m_hud_name );
	std::transform( weapon_name.begin( ), weapon_name.end( ), weapon_name.begin( ), std::toupper );

	m_render.draw_text( m_render.m_fonts.main,
		m_box.x + m_box.width / 2, m_box.y + m_box.height + gap,
		weapon_name,
		m_player.m_colors.light,
		x_centre );

}

void visuals::draw_ammo( ) {

	if ( !m_config.m_esp.player_ammo )
		return;

	if ( !m_weapon.pointer )
		return;

	float scaler = static_cast< float >( m_weapon.pointer->get_ammo( ) ) / static_cast< float >( m_weapon.info->m_max_clip1 );

	animation_layer* animation_layer_weapon_action = m_player.pointer->get_anim_overlay( 1 );
	if ( animation_layer_weapon_action ) {

		int activity = m_player.pointer->get_sequence_activity( animation_layer_weapon_action->m_sequence );
		if ( activity == 967 && animation_layer_weapon_action->m_weight != 0.f )
			scaler = animation_layer_weapon_action->m_cycle;

	}

	m_render.draw_filled_rect( m_box.x, m_box.y + m_box.height + 2,
		m_box.width, 4,
		m_player.m_colors.dark );

	m_render.draw_filled_rect( m_box.x + 1, m_box.y + m_box.height + 3,
		static_cast< int >( m_box.width * scaler - 2 ), 2,
		color( 0, 128, 255, m_alpha[ m_player.index - 1 ] ) );

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