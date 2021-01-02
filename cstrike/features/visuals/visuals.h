#pragma once

#include <array>

#include "../../cstrike.h"

struct visuals {

	void paint( );

private:

	void draw_box( );

	void draw_health( );

	void draw_name( );

	void draw_weapon( );

	void calculate_alpha( );

	bool calculate_box( );

	struct {

		int x, y, width, height;

	} m_box;

	struct {

		cs_player* pointer;
		
		int index;

		bool is_dormant;

	} m_player;

	std::array< int, 64 > m_alpha;

	h_font m_font = 0x5;

};

inline visuals m_visuals;