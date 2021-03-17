#pragma once

#include <windows.h>
#include <string>

#include "../memory/address.h"

struct pattern {

	// will eventually get my lazy ass to write a better scanner
	address find( std::size_t base , std::string_view pattern );

};

inline pattern m_pattern;