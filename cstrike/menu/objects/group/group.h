#pragma once

#include "../object.h"

struct group {

	group( int x, int y, int width, int height );

	void draw( );

	void setup_checkbox( std::string_view name, bool* item );

	void setup_slider( std::string_view name, int* item, int min, int max );

private:

	int get_height( );

	int m_gap = 5;

	struct {

		int x, y, width, height;

	} m_size;

	std::vector< std::shared_ptr< object > > m_objects;

};