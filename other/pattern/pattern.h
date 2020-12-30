#pragma once

#include <windows.h>
#include <string>

#include "../memory/address.h"

struct pattern {

	address find( const std::string_view module_name, const std::string_view pattern );

};

inline pattern m_pattern;