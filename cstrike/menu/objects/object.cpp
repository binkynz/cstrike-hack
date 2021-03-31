#include "object.h"

#include "../menu.h"

object::object( std::string_view name, int x, int y ) {

	m_name = name;

	m_size.x = x;
	m_size.y = y;

}