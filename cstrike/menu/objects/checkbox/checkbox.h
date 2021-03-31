#pragma once

#include "../object.h"

struct checkbox : public object {

	checkbox( std::string_view name, int x, int y );

	void set_size( int size );
	void set_item( bool* item );

	void draw( );

	void think( );

	int get_height( ) {

		return m_height + m_gap;

	}

private:

	int m_height;

	bool* m_item;

};