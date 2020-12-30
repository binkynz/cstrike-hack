#pragma once

#include <cstddef>
#include <string>
#include <unordered_map>
#include <fstream>

#include "../client_class.h"

struct netvars {

	bool setup( );

	void store( const std::string_view name, recv_table* table, std::size_t offset = 0 );

	std::unordered_map< std::size_t, std::size_t > m_offsets;

private:

	std::ofstream m_file;

};

inline netvars m_netvars;