#pragma once

#include <cstddef>
#include <string>

struct hash {

	std::size_t get( std::string_view string );

private:

	std::size_t m_basis = 0x8adf9ed5;
	std::size_t m_prime = 0x60561129;

};

inline hash m_hash;