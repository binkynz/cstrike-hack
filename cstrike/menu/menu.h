#pragma once

#include "../cstrike.h"

#include "objects/objects.h"

struct menu {

	bool setup( );

	void paint( );

	struct {

		int x, y, width, height;

		int gap;

	} m_size;

	struct {

		color dark, light, vibrant;

	} m_colors;

private:

	void setup_tab( std::string_view name, std::function< void( tab* ) > function );

	void handle_movement( );

	void draw_backplate( );

	void process_tabs( );

	struct {

		bool active;
		int x, y;

	} m_drag;

	int m_selected_tab;

	std::vector< tab > m_tabs;

};

inline menu m_menu;