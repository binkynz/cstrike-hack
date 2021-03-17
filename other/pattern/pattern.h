#pragma once

#include <windows.h>
#include <string>

#include "../memory/address.h"

struct pattern {

	address find( std::uintptr_t base , std::string_view pattern );

};

inline pattern m_pattern;