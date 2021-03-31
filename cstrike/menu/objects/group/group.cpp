#include "group.h"

#include "../../menu.h"

#include "../checkbox/checkbox.h"
#include "../slider/slider.h"

group::group( int x, int y, int width, int height ) {

	m_size = {

		x,
		y,
		width,
		height

	};

}

void group::draw( ) {

	m_render.draw_outlined_rect( m_menu.m_size.x + m_size.x, m_menu.m_size.y + m_size.y, 
		m_size.width, m_size.height, 
		m_menu.m_colors.light );

	for ( auto o : m_objects ) {

		o->draw( );

		o->think( );

	}

}

void group::setup_checkbox( std::string_view name, bool* item ) {

	int x = m_size.x + m_gap,
		y = m_size.y + get_height( ) + m_gap;

	auto obj = std::shared_ptr< checkbox >( new checkbox( name, x, y ) );

	obj->set_size( 10 );
	obj->set_item( item );

	m_objects.push_back( std::move( obj ) );

}

void group::setup_slider( std::string_view name, int* item, int min, int max ) {

	int x = m_size.x + m_gap,
		y = m_size.y + get_height( ) + m_gap;

	auto obj = std::shared_ptr< slider >( new slider( name, x, y ) );

	obj->set_size( 100, 10 );
	obj->set_item( item );
	obj->set_range( min, max );

	m_objects.push_back( std::move( obj ) );

}

int group::get_height( ) {

	int height = 0;

	for ( auto obj : m_objects )
		height += obj->get_height( );

	return height;

}