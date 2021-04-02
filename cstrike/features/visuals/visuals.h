#pragma once

#include <array>

#include "../../cstrike.h"

struct visuals {

	void paint( );

private:

	void draw_watermark( );

	void draw_local_info( );

	void draw_box( );

	void draw_health( );

	void draw_name( );

	void draw_weapon( );

	void draw_ammo( );

	void calculate_alpha( );

	bool calculate_box( );

	struct {

		int x, y, width, height;

	} m_box;

	struct {

		cs_player* pointer;
		
		int index;

		bool is_dormant;

		struct {

			color dark, light;

		} m_colors;

	} m_player;

	struct {

		weapon_cs_base* pointer;

		cs_weapon_info* info;

	} m_weapon;

	struct {

		color light = color( 255, 255, 255 );

	} m_colors;

	std::array< int, 64 > m_alpha;

};

inline visuals m_visuals;