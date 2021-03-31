#pragma once

#include "../object.h"

struct slider : public object {

	slider( std::string_view name, int x, int y );

	void set_size( int width, int height );
	void set_item( int* item );
	void set_range( int min, int max );

	void draw( );

	void think( );

	int get_height( ) {

		return m_height + m_gap;

	}

private:

	int m_width;
	int m_height;

	int* m_item;

	int m_min;
	int m_max;

	bool m_active = false;

};