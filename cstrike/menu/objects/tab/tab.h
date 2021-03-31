#pragma once

#include "../object.h"

#include "../group/group.h"

struct tab {

	tab( std::string_view name );

	void draw( int x, int y, bool is_selected );

	void setup_group( int x, int y, int width, int height, std::function< void( group* ) > function );

private:

	std::string m_name;

	std::vector< group > m_groups;

};