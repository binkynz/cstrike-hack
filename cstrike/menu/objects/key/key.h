#pragma once

#include "../object.h"

struct key : public object {

	key( std::string_view name, int x, int y );

	void set_size( int width, int height );
	void set_item( int* item );

	void draw( );

	void think( );

	int get_height( ) {

		return m_height + m_gap;

	}

private:

	int m_width;
	int m_height;

	int* m_item;

	bool m_active = false;

};